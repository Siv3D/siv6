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
			return fs::path(Unicode::ToWstring(path));
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
			const std::wstring pathW = Unicode::ToWstring(path);

			return (::FindResourceW(::GetModuleHandleW(nullptr), &pathW[1], L"FILE") != nullptr);
		}

		[[nodiscard]]
		static int64 ResourceSize(const FilePathView path)
		{
			HMODULE module = ::GetModuleHandleW(nullptr);
			std::wstring resourceName = Unicode::ToWstring(path);
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
				return FilePath();
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
				return FilePath();
			}
			else if (length > std::size(result)) [[unlikely]]
			{
				std::wstring result2(length - 1, L'\0');
				const DWORD length2 = ::GetFullPathNameW(wpath.c_str(), length, result2.data(), &pFilePart);

				if ((length2 == 0) || (length2 > length))
				{
					return FilePath();
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
	}
}
