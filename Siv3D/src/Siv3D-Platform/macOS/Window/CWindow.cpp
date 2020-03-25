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
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/UserAction.hpp>
# include <Siv3D/UserAction/IUserAction.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
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
		
		//::glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
		
		if (!::glfwInit())
		{
			throw EngineError(U"glfwInit() failed");
		}

		::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	
		m_window = ::glfwCreateWindow(m_clientSize.x, m_clientSize.y,
									  m_actualTitle.narrow().c_str(), nullptr, nullptr);
		
		if (!m_window)
		{
			throw EngineError(U"glfwCreateWindow() failed");
		}
	}

	void CWindow::update()
	{
		::glfwPollEvents();
		
		if (::glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::AnyKeyDown | UserAction::EscapeKeyDown);
		}
		
		if (::glfwGetWindowAttrib(m_window, GLFW_FOCUSED) == GLFW_FALSE)
		{
			SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::WindowDeactivated);
		}
		
		if (::glfwWindowShouldClose(m_window))
		{
			SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::CloseButtonClicked);

			::glfwSetWindowShouldClose(m_window, GLFW_FALSE);
		}
	}
}
