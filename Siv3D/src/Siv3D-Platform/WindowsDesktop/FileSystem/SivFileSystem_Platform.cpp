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
		static fs::path ToPath(const FilePathView path)
		{
			return fs::path(Unicode::ToWstring(path));
		}

		static fs::file_status ToStatus(const FilePathView path)
		{
			return fs::status(detail::ToPath(path));
		}

		inline bool IsDirectory(const fs::file_status& status) noexcept
		{
			return (status.type() == fs::file_type::directory);
		}

		static FilePath NormalizePath(FilePath path, const bool skipDirectoryCheck = false)
		{
			path.replace(U'\\', U'/');

			if (!path.ends_with(U'/')
				&& (skipDirectoryCheck || IsDirectory(detail::ToStatus(path))))
			{
				path.push_back(U'/');
			}

			return path;
		}

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
