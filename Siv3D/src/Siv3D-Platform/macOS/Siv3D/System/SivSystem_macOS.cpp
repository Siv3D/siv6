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

# include <Siv3D/System.hpp>
# include <Siv3D/FileSystem.hpp>
# import <Cocoa/Cocoa.h>

namespace s3d
{
	namespace detail
	{
		static bool MacOS_LaunchBrowser(const char* url)
		{
			@autoreleasepool
			{
				NSString* str = [NSString stringWithCString:url encoding:NSUTF8StringEncoding];
				NSURL* ns_url = [NSURL URLWithString:str];
				
				const bool result = [[NSWorkspace sharedWorkspace]
									openURLs:@[ns_url]
									withAppBundleIdentifier:nil
									options:NSWorkspaceLaunchDefault
									additionalEventParamDescriptor:nil
									launchIdentifiers:nil];
				
				return result;
			}
		}
	}

	namespace System
	{
			String url{ _url };
			const bool isWebPage = url.starts_with(U"http://")
				|| url.starts_with(U"https://");

			if (!isWebPage)
			{
				const String extension = FileSystem::Extension(_url);
				const bool isHTML = (extension == U"html") || (extension == U"htm");

				if (!isHTML)
				{
					return false;
				}

				url = (U"file://" + FileSystem::FullPath(_url));
			}

			return detail::MacOS_LaunchBrowser(url.narrow().c_str());
		}
	}
}
