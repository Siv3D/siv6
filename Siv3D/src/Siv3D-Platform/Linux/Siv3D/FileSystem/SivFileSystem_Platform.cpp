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
		[[nodiscard]]
		static fs::path ToPath(const FilePathView path)
		{
			return fs::path(Unicode::ToWstring(path));
		}

		[[nodiscard]]
		static fs::file_status GetStatus(const FilePathView path)
		{
			return fs::status(detail::ToPath(path));
		}	

		[[nodiscard]]
		static bool GetStat(const FilePathView path, struct stat& s)
		{
			return (::stat(FilePath(path).replaced(U'\\', U'/').narrow().c_str(), &s) == 0);
		}	

		[[nodiscard]]
		static bool Exists(const FilePathView path)
		{
			struct stat s;
			return GetStat(path, s);
		}

		[[nodiscard]]
		static bool IsRegular(const FilePathView path)
		{
			struct stat s;
			if (!GetStat(path, s))
			{
				return false;
			}

			return S_ISREG(s.st_mode);
		}

		[[nodiscard]]
		static bool IsDirectory(const FilePathView path)
		{
			struct stat s;
			if (!GetStat(path, s))
			{
				return false;
			}

			return S_ISDIR(s.st_mode);
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
		static DateTime ToDateTime(const ::timespec& tv)
		{
			::tm lt;
			::localtime_r(&tv.tv_sec, &lt);
			return{ (1900 + lt.tm_year),
					(1 + lt.tm_mon),
					(lt.tm_mday),
					lt.tm_hour,
					lt.tm_min,
					lt.tm_sec,
					static_cast<int32>(tv.tv_nsec / (1'000'000))};
		}		

		namespace init
		{
			const static FilePath g_initialPath = NormalizePath(Unicode::Widen(fs::current_path().string()));

			static FilePath g_modulePath;

			void InitModulePath(const char* arg)
			{
				g_modulePath = Unicode::Widen(arg);
			}
		}
	}

	namespace FileSystem
	{
		bool IsResourcePath(const FilePathView path) noexcept
		{
			const FilePath resourceDirectory = FileSystem::ModulePath() + U"/resources/";

			return FullPath(path).starts_with(resourceDirectory);
		}

		bool Exists(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return false;
			}

			return detail::Exists(path);
		}

		bool IsDirectory(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return false;
			}

			return detail::IsDirectory(path);
		}

		bool IsFile(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return false;
			}

			return detail::IsRegular(path);
		}

		bool IsResource(const FilePathView path)
		{
			return IsResourcePath(path)
				&& detail::Exists(path);
		}

		FilePath FullPath(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return FilePath{};
			}

			return detail::NormalizePath(Unicode::Widen(fs::weakly_canonical(detail::ToPath(path)).string()));
		}

		Platform::NativeFilePath NativePath(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return Platform::NativeFilePath{};
			}

			return fs::weakly_canonical(detail::ToPath(path)).string();
		}

		FilePath VolumePath(const FilePathView path)
		{
			return U"/";
		}

		bool IsEmptyDirectory(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return false;
			}

			struct stat s;
			if (!detail::GetStat(path, s))
			{
				return false;
			}

			if (S_ISDIR(s.st_mode))
			{
				return (fs::directory_iterator(fs::path(path.toWstr())) == fs::directory_iterator());
			}
			else
			{
				return false;
			}
		}

		int64 Size(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return 0;
			}
			
			struct stat s;
			if (!detail::GetStat(FilePath(path), s))
			{
				return 0;
			}
			
			if (S_ISREG(s.st_mode))
			{
				return s.st_size;
			}
			else if (S_ISDIR(s.st_mode))
			{
				int64 result = 0;
				
				for (const auto& v : fs::recursive_directory_iterator(path.narrow()))
				{
					struct stat s;
					
					if (::stat(v.path().c_str(), &s) != 0 || S_ISDIR(s.st_mode))
					{
						continue;
					}
					
					result += s.st_size;
				}
				
				return result;
			}
			else
			{
				return 0;
			}
		}

		int64 FileSize(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
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

		Optional<DateTime> CreationTime(const FilePathView path)
		{
			struct stat s;
			if (!detail::GetStat(path, s))
			{
				return none;
			}
			
			return detail::ToDateTime(s.st_birthtimespec);
		}

		Optional<DateTime> WriteTime(const FilePathView path)
		{
			struct stat s;
			if (!detail::GetStat(path, s))
			{
				return none;
			}
			
			return detail::ToDateTime(s.st_mtimespec);
		}
		
		Optional<DateTime> AccessTime(const FilePathView path)
		{
			struct stat s;
			if (!detail::GetStat(path, s))
			{
				return none;
			}
			
			return detail::ToDateTime(s.st_atimespec);
		}

		Array<FilePath> DirectoryContents(const FilePathView path, const bool recursive)
		{
			Array<FilePath> paths;

			if (not path) SIV3D_UNLIKELY
			{
				return paths;
			}

			if (detail::GetStatus(path).type() != fs::file_type::directory)
			{
				return paths;
			}

			if (recursive)
			{
				for (const auto& v : fs::recursive_directory_iterator(path.narrow()))
				{
					paths.push_back(Unicode::Widen(v.path().string()));
				}
			}
			else
			{
				for (const auto& v : fs::directory_iterator(path.narrow()))
				{
					paths.push_back(Unicode::Widen(v.path().string()));
				}
			}

			return paths;
		}

		const FilePath& InitialDirectory() noexcept
		{
			return detail::init::g_initialPath;
		}

		const FilePath& ModulePath() noexcept
		{
			return detail::init::g_modulePath;
		}

		FilePath CurrentDirectory()
		{
			return detail::NormalizePath(Unicode::Widen(fs::current_path().string()));
		}
	}
}
