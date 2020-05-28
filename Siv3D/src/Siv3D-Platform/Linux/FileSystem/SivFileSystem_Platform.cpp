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

# include <sys/stat.h>
# include <filesystem>
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


		static bool GetStat(const FilePathView path, struct stat& s)
		{
			return (::stat(FilePath(path).replaced(U'\\', U'/').narrow().c_str(), &s) == 0);
		}

		inline bool IsDirectory(const fs::file_status& status) noexcept
		{
			return (status.type() == fs::file_type::directory);
		}		

		static bool IsNotFound(const FilePathView path)
		{
			struct stat s;
			return (not GetStat(path, s));
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
	}

	namespace FileSystem
	{
		FilePath FullPath(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return FilePath();
			}

			return detail::NormalizePath(Unicode::Widen(fs::weakly_canonical(detail::ToPath(path)).string()));
		}

		int64 FileSize(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return 0;
			}
			
			struct stat s;
			if (!detail::GetStat(path, s))
			{
				return 0;
			}
			
			if (!S_ISREG(s.st_mode))
			{
				return 0;
			}
			
			return s.st_size;
		}
	}
}
