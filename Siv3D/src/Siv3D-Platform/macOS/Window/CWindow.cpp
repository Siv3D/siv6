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

# include <Siv3D/Error.hpp>
# include "CWindow.hpp"

namespace s3d
{
	CWindow::CWindow()
	{

	}

	CWindow::~CWindow()
	{
		LOG_SCOPED_TRACE(U"CWindow::~CWindow()");
		
		::glfwTerminate();
	}

	void CWindow::init()
	{
		LOG_SCOPED_TRACE(U"CWindow::init()");
		
		::glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
		
		if (!::glfwInit())
		{
			throw EngineError(U"glfwInit() failed");
		}

		::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		
		m_window = ::glfwCreateWindow(m_clientSize.x, m_clientSize.y,
									  m_actualTitle.narrow().c_str(), nullptr, nullptr);
		
		if (!m_window)
		{
			throw EngineError(U"glfwCreateWindow() failed. [OpenGL 4.1 is not supported]");
		}
	}
}
