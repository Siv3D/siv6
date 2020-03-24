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

# include <Siv3D/Windows/Windows.hpp>
# include <ShellScalingApi.h> // for SetProcessDpiAwareness()
# include <Siv3D/StringView.hpp>
# include <Siv3D/DLL.hpp>

namespace s3d::detail
{
	void SetDPIAwareness()
	{
		LOG_SCOPED_TRACE(U"SetDPIAwareness()");

		// Windows 10 1607-
		if (const HMODULE user32 = DLL::LoadSystemLibrary(L"user32.dll"))
		{
			decltype(SetThreadDpiAwarenessContext)* p_SetThreadDpiAwarenessContext = DLL::GetFunctionNoThrow(user32, "SetThreadDpiAwarenessContext");

			if (p_SetThreadDpiAwarenessContext)
			{
				LOG_VERBOSE(U"SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)");
				p_SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
				::FreeLibrary(user32);
				return;
			}

			::FreeLibrary(user32);
		}

		// Windows 8.1-
		if (const HMODULE shcore = DLL::LoadSystemLibrary(L"shcore.dll"))
		{
			decltype(SetProcessDpiAwareness)* p_SetProcessDpiAwareness = DLL::GetFunctionNoThrow(shcore, "SetProcessDpiAwareness");

			if (p_SetProcessDpiAwareness)
			{
				LOG_VERBOSE(U"SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE)");
				p_SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
				::FreeLibrary(shcore);
				return;
			}

			::FreeLibrary(shcore);
		}

		// Windows Vista-
		LOG_VERBOSE(U"SetProcessDPIAware()");
		::SetProcessDPIAware();
	}
}
