//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <filesystem>
# include <Siv3D/Common.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace fs = std::filesystem;

	namespace detail
	{
		[[nodiscard]]
		inline static fs::path ToPath(const FilePathView path)
		{
			return fs::path(path.toWstr());
		}

		[[nodiscard]]
		inline static fs::file_status GetStatus(const FilePathView path)
		{
			return fs::status(detail::ToPath(path));
		}

		[[nodiscard]]
		static FilePath NormalizePath(FilePath path, const bool skipDirectoryCheck = false)
		{
			path.replace(U'\\', U'/');

			if (!path.ends_with(U'/')
				&& (skipDirectoryCheck || (GetStatus(path).type() == fs::file_type::directory)))
			{
				path.push_back(U'/');
			}

			return path;
		}

		[[nodiscard]]
		static bool ResourceExists(const FilePathView path)
		{
			const std::wstring pathW = path.toWstr();

			return (::FindResourceW(::GetModuleHandleW(nullptr), &pathW[1], L"FILE") != nullptr);
		}

		[[nodiscard]]
		static int64 ResourceSize(const FilePathView path)
		{
			HMODULE module = ::GetModuleHandleW(nullptr);
			std::wstring resourceName = path.toWstr();
			resourceName.front() = L'#';

			if (HRSRC hrs = ::FindResourceW(module, resourceName.c_str(), L"FILE"))
			{
				return ::SizeofResource(module, hrs);
			}
			else
			{
				return 0;
			}
		}

		[[nodiscard]]
		static int64 DirectorySizeRecursive(FilePath directory)
		{
			directory = NormalizePath(directory, true);

			WIN32_FIND_DATAW data;
			HANDLE sh = ::FindFirstFileW((directory + U'*').toWstr().c_str(), &data);

			if (sh == INVALID_HANDLE_VALUE)
			{
				return 0;
			}

			int64 result = 0;

			do
			{
				if (!(data.cFileName[0] == L'.' && data.cFileName[1] == L'\0')
					&& !(data.cFileName[0] == L'.' && data.cFileName[1] == L'.' && data.cFileName[2] == L'\0'))
				{
					if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						result += DirectorySizeRecursive((directory + Unicode::FromWstring(data.cFileName)) + U'/');
					}
					else
					{
						result += (static_cast<uint64>(data.nFileSizeHigh) << 32) + data.nFileSizeLow;
					}
				}

			} while (::FindNextFileW(sh, &data));

			::FindClose(sh);

			return result;
		}

		static void DirectoryContentsRecursive(FilePath directory, Array<FilePath>& paths, const bool recursive)
		{
			directory = NormalizePath(directory, true);

			WIN32_FIND_DATAW data;
			HANDLE sh = ::FindFirstFileW((directory + U'*').toWstr().c_str(), &data);

			if (sh == INVALID_HANDLE_VALUE)
			{
				return;
			}

			do
			{
				if (!(data.cFileName[0] == L'.' && data.cFileName[1] == L'\0')
					&& !(data.cFileName[0] == L'.' && data.cFileName[1] == L'.' && data.cFileName[2] == L'\0'))
				{
					paths.push_back(directory + Unicode::FromWstring(data.cFileName));

					if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						paths.back().push_back(U'/');

						if (recursive)
						{
							DirectoryContentsRecursive(paths.back(), paths, true);
						}
					}
				}

			} while (::FindNextFileW(sh, &data));

			::FindClose(sh);
		}

		[[nodiscard]]
		static DateTime FiletimeToTime(FILETIME& in)
		{
			SYSTEMTIME systemtime;
			::FileTimeToLocalFileTime(&in, &in);
			::FileTimeToSystemTime(&in, &systemtime);

			return{ systemtime.wYear, systemtime.wMonth, systemtime.wDay,
				systemtime.wHour, systemtime.wMinute, systemtime.wSecond, systemtime.wMilliseconds };
		}

		namespace init
		{
			const static FilePath g_initialDirectory = FileSystem::CurrentDirectory();

			const static FilePath g_modulePath = []()
			{
				wchar_t result[1024];
				const DWORD length = ::GetModuleFileNameW(nullptr, result, _countof(result));

				if ((length == 0) || (length >= _countof(result)))
				{
					return FilePath{};
				}

				return NormalizePath(Unicode::FromWstring(std::wstring_view(result, length)));
			}();
		}
	}

	namespace FileSystem
	{
		bool IsResourcePath(const FilePathView path) noexcept
		{
			return path.starts_with(U'/');
		}

		bool Exists(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return false;
			}

			if (IsResourcePath(path))
			{
				return detail::ResourceExists(path);
			}

			return (detail::GetStatus(path).type() != fs::file_type::not_found);
		}

		bool IsDirectory(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return false;
			}

			if (IsResourcePath(path))
			{
				return false;
			}

			return (detail::GetStatus(path).type() == fs::file_type::directory);
		}

		bool IsFile(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return false;
			}

			if (IsResourcePath(path))
			{
				return detail::ResourceExists(path);
			}

			return (detail::GetStatus(path).type() == fs::file_type::regular);
		}

		bool IsResource(const FilePathView path)
		{
			return IsResourcePath(path)
				&& detail::ResourceExists(path);
		}

		FilePath FullPath(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return FilePath{};
			}

			if (IsResourcePath(path)) [[unlikely]]
			{
				return FilePath(path);
			}

			const std::wstring wpath = path.toWstr();
			wchar_t result[1024];
			wchar_t* pFilePart = nullptr;
			const DWORD length = ::GetFullPathNameW(wpath.c_str(), _countof(result), result, &pFilePart);

			if (length == 0) [[unlikely]]
			{
				return FilePath{};
			}
			else if (length > std::size(result)) [[unlikely]]
			{
				std::wstring result2(length - 1, L'\0');
				const DWORD length2 = ::GetFullPathNameW(wpath.c_str(), length, result2.data(), &pFilePart);

				if ((length2 == 0) || (length2 > length))
				{
					return FilePath{};
				}

				const bool isDirectory = (pFilePart == nullptr);
				return detail::NormalizePath(Unicode::FromWstring(result2), isDirectory);
			}

			const bool isDirectory = (pFilePart == nullptr);
			return detail::NormalizePath(Unicode::FromWstring(std::wstring_view(result, length)), isDirectory);
		}

		Platform::NativeFilePath NativePath(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return Platform::NativeFilePath{};
			}

			if (IsResourcePath(path)) [[unlikely]]
			{
				return Platform::NativeFilePath{};
			}

			const std::wstring wpath = path.toWstr();
			wchar_t result[1024];
			wchar_t* pFilePart = nullptr;
			const DWORD length = ::GetFullPathNameW(wpath.c_str(), _countof(result), result, &pFilePart);

			if (length == 0) [[unlikely]]
			{
				return Platform::NativeFilePath{};
			}
			else if (length > std::size(result)) [[unlikely]]
			{
				std::wstring result2(length - 1, L'\0');
				const DWORD length2 = ::GetFullPathNameW(wpath.c_str(), length, result2.data(), &pFilePart);

				if ((length2 == 0) || (length2 > length))
				{
					return Platform::NativeFilePath{};
				}

				return result2;
			}

			return std::wstring(result, length);
		}

		FilePath VolumePath(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return 0;
			}

			if (IsResourcePath(path))
			{
				return FilePath{};
			}

			const std::wstring wpath = path.toWstr();
			wchar_t result[MAX_PATH];

			if (::GetVolumePathNameW(wpath.c_str(), result, _countof(result)) == 0)
			{
				return FilePath();
			}

			return Unicode::FromWstring(result).replace(U'\\', U'/');
		}

		bool IsEmptyDirectory(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return 0;
			}

			if (IsResourcePath(path))
			{
				return false;
			}

			const auto fpath = detail::ToPath(path);

			if (detail::GetStatus(path).type() != fs::file_type::directory)
			{
				return false;
			}

			return (fs::directory_iterator(fpath) == fs::directory_iterator());
		}

		int64 Size(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return 0;
			}

			if (IsResourcePath(path))
			{
				return detail::ResourceSize(path);
			}

			const auto fpath = detail::ToPath(path);
			const auto type = fs::status(fpath).type();

			if (type == fs::file_type::regular)
			{
				WIN32_FILE_ATTRIBUTE_DATA fad;

				if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
				{
					return 0;
				}

				return ((static_cast<uint64>(fad.nFileSizeHigh) << 32) + fad.nFileSizeLow);
			}
			else if (type == fs::file_type::directory)
			{
				return detail::DirectorySizeRecursive(FullPath(path));
			}
			else
			{
				return 0;
			}
		}

		int64 FileSize(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return 0;
			}

			if (IsResourcePath(path))
			{
				return detail::ResourceSize(path);
			}

			WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0) [[unlikely]]
			{
				return 0;
			}

			// ディレクトリの場合は 0
			if (fad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				return 0;
			}

			return ((static_cast<uint64>(fad.nFileSizeHigh) << 32) + fad.nFileSizeLow);
		}

		Optional<DateTime> CreationTime(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return none;
			}

			if (IsResourcePath(path))
			{
				return CreationTime(ModulePath());
			}

			WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftCreationTime);
		}

		Optional<DateTime> WriteTime(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return none;
			}

			if (IsResourcePath(path))
			{
				return WriteTime(ModulePath());
			}

			WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftLastWriteTime);
		}

		Optional<DateTime> AccessTime(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return none;
			}

			if (IsResourcePath(path))
			{
				return AccessTime(ModulePath());
			}

			WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftLastAccessTime);
		}

		Array<FilePath> DirectoryContents(const FilePathView path, const bool recursive)
		{
			Array<FilePath> paths;

			if (not path) [[unlikely]]
			{
				return paths;
			}

			if (IsResourcePath(path))
			{
				return paths;
			}

			if (detail::GetStatus(path).type() != fs::file_type::directory)
			{
				return paths;
			}

			detail::DirectoryContentsRecursive(FullPath(path), paths, recursive);

			return paths;
		}

		const FilePath& InitialDirectory() noexcept
		{
			return detail::init::g_initialDirectory;
		}

		const FilePath& ModulePath() noexcept
		{
			return detail::init::g_modulePath;
		}

		FilePath CurrentDirectory()
		{
			wchar_t result[1024];
			const DWORD length = ::GetCurrentDirectoryW(_countof(result), result);

			if (length == 0)
			{
				return FilePath{};
			}
			else if (length > std::size(result))
			{
				std::wstring result2(length - 1, L'\0');
				const DWORD length2 = ::GetCurrentDirectoryW(length, result2.data());

				if ((length2 == 0) || (length2 > length))
				{
					return FilePath{};
				}

				return detail::NormalizePath(Unicode::FromWstring(result2), true);
			}

			return detail::NormalizePath(Unicode::FromWstring(std::wstring_view(result, length)), true);
		}
	}
}
