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
# import  <Foundation/Foundation.h>

namespace s3d
{
	namespace detail
	{
		static bool GetStat(const FilePathView path, struct stat& s)
		{
			return (::stat(FilePath(path).replaced(U'\\', U'/').narrow().c_str(), &s) == 0);
		}
	
		static bool IsDirectory(const FilePathView path)
		{
			struct stat s;
			if (!GetStat(path, s))
			{
				return false;
			}
			
			return S_ISDIR(s.st_mode);
		}
	
		static std::string MacOS_FullPath(const char* _path, bool isRelative)
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

	namespace FileSystem
	{
		bool IsDirectory(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return false;
			}
			
			return detail::IsDirectory(path);
		}

		FilePath FullPath(const FilePathView path)
		{
			if (not path) [[unlikely]]
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
