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

# include <GLFW/glfw3.h>
# define GLFW_EXPOSE_NATIVE_COCOA
# include <GLFW/glfw3native.h>
# include <Siv3D/WindowState.hpp>

namespace s3d
{
	void Siv3D_MacOS_UpdateWindowState(GLFWwindow* handle, WindowState& state)
	{
		NSWindow* window = glfwGetCocoaWindow(handle);
		
		//state.maximized = false;//([window isZoomed] && (state.style != WindowStyle::Frameless));
		
		CGFloat contentHeight = [window contentRectForFrameRect: window.frame].size.height;
		state.titleBarHeight = (window.frame.size.height - contentHeight);
	}
}
