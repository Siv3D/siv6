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
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>
# include <mach-o/dyld.h>
# import  <Foundation/Foundation.h>

namespace s3d
{
	namespace detail
	{
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
			for (auto& ch : path)
			{
				if (ch == U'\\')
				{
					ch = U'/';
				}
			}
			
			if (!path.ends_with(U'/') && (skipDirectoryCheck || IsDirectory(path)))
			{
				path.push_back(U'/');
			}
			
			return path;
		}
	
		[[nodiscard]]
		static std::string MacOS_FullPath(const char* _path, bool isRelative)
		{
			@autoreleasepool
			{
				NSString* path = [NSString stringWithUTF8String:_path];
				
				if (isRelative)
				{
					NSURL* bundle = [[NSBundle mainBundle] bundleURL];
					NSURL* file = [NSURL fileURLWithPath:path relativeToURL:bundle];
					NSURL* absolutePath = [file absoluteURL];
					NSString* str = [absolutePath path];
					return std::string([str UTF8String], [str lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);
				}
				else
				{
					NSURL* file = [NSURL fileURLWithPath:path];
					NSURL* absolutePath = [file absoluteURL];
					NSString* str = [absolutePath path];
					return std::string([str UTF8String], [str lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);
				}
			}
		}
	
		[[nodiscard]]
		static std::string MacOS_CurrentPath()
		{
			@autoreleasepool
			{
				NSDictionary* env = [[NSProcessInfo processInfo] environment];
				
				if (NSString* current = env[@"PWD"])
				{
					return [current UTF8String];
				}
				else if (NSString* current = [[NSFileManager defaultManager] currentDirectoryPath]) // requires permission
				{
					return [current UTF8String];
				}
			
				return "";
			}
		}
	
		namespace init
		{
			FilePath ParentPath(FilePath path, size_t n)
			{
				if (path.count(U'/') <= n)
				{
					return FilePath(U"NN");
				}

				while (path)
				{
					if (path.back() == U'/')
					{
						if (n == 0)
						{
							break;
						}
						
						--n;
					}
					
					path.pop_back();
				}
				
				return path;
			}
		
			static FilePath g_initialPath = []()
			{
				char path_str[4096];
				uint32_t bufferSize = sizeof(path_str);

				if (_NSGetExecutablePath(path_str, &bufferSize) != 0)
				{
					return FilePath{};
				}

				const String path = Unicode::Widen(path_str);

				FilePath modulePath = ParentPath(path, 2);

				if (modulePath.ends_with(U'/'))
				{
					modulePath.pop_back();
				}

				return ParentPath(path, 3);
			}();
		
			static FilePath g_modulePath = []()
			{
				char path_str[4096];
				uint32_t bufferSize = sizeof(path_str);

				if (_NSGetExecutablePath(path_str, &bufferSize) != 0)
				{
					return FilePath{};
				}

				const String path = Unicode::Widen(path_str);

				FilePath modulePath = ParentPath(path, 2);

				if (modulePath.ends_with(U'/'))
				{
					modulePath.pop_back();
				}

				return modulePath;
			}();
			
			//static bool g_isSandBoxed;
			
			void SetInitialPath(FilePath& path)
			{
				g_initialPath = std::move(path);
			}
		
			void SetModulePath(FilePath&& path)
			{
				g_modulePath = std::move(path);
				
				//g_isSandBoxed = FileSystem::SpecialFolderPath(SpecialFolder::Caches).includes(U"/Library/Containers/");
			}
		}
	}

	namespace FileSystem
	{
		bool IsResourcePath(const FilePathView path) noexcept
		{
			const FilePath resourceDirectory = FileSystem::ModulePath() + U"/Contents/Resources/";

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
				return FilePath();
			}
			
			FilePath src;
			bool isRelative = false;
			
			if (path.starts_with(U"/Users/"))
			{
				src = path;
			}
			else
			{
				src = (U"../" + path);
				isRelative = true;
			}
			
			FilePath result = Unicode::Widen(detail::MacOS_FullPath(src.toUTF8().c_str(), isRelative));
			
			if (result.starts_with(U"file://"))
			{
				result.erase(result.begin(), result.begin() + 7);
			}
			
			if (IsDirectory(result) && !result.ends_with(U'/'))
			{
				result.push_back(U'/');
			}
			
			return result;
		}
	
		Platform::NativeFilePath NativePath(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return Platform::NativeFilePath();
			}
			
			FilePath src;
			bool isRelative = false;
			
			if (path.starts_with(U"/Users/"))
			{
				src = path;
			}
			else
			{
				src = U"../" + path;
				isRelative = true;
			}
			
			return detail::MacOS_FullPath(src.toUTF8().c_str(), isRelative);
		}
	
		FilePath VolumePath(const FilePathView)
		{
			// [Siv3D ToDo]
			return U"/";
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
			return detail::NormalizePath(Unicode::Widen(detail::MacOS_CurrentPath()));
		}
	}
}
