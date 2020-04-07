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
# include <Siv3D/Profiler/IProfiler.hpp>
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
		
		const bool useMetal = false;

		if constexpr (useMetal)
		{
			// Metal
			::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		}
		else
		{
			// OpenGL 4.1
			::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
			::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			::glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, SIV3D_BUILD(DEBUG) ? GLFW_TRUE : GLFW_FALSE);
		}
		
		::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	
		m_window = ::glfwCreateWindow(m_state.virtualSize.x, m_state.virtualSize.y,
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
		
		if constexpr (SIV3D_BUILD(DEBUG))
		{
			setWindowTitle(m_title);
		}
	}

	void CWindow::setWindowTitle(const String& title)
	{
		String newActualTitle = title;
		
		if constexpr (SIV3D_BUILD(DEBUG))
		{
			const String statistics = SIV3D_ENGINE(Profiler)->getSimpleStatistics();
			newActualTitle += U" (Debug Build) | ";
			newActualTitle += statistics;
		}

		if (m_actualTitle != newActualTitle)
		{
			::glfwSetWindowTitle(m_window, newActualTitle.narrow().c_str());
			m_actualTitle.swap(newActualTitle);
		}

		m_title = title;
	}

	const String& CWindow::getWindowTitle() const noexcept
	{
		return m_title;
	}

	void* CWindow::getHandle() const noexcept
	{
		return m_window;
	}

	const WindowState& CWindow::getState() const noexcept
	{
		return m_state;
	}

	void CWindow::setStyle(const WindowStyle style)
	{
	
	}

	void CWindow::setPos(const Point& pos)
	{
	
	}

	void CWindow::maximize()
	{
		LOG_TRACE(U"CWindow::maximize()");

		if (m_state.style == WindowStyle::Fixed)
		{
			//LOG_FAIL(U"A window with WindowStyle::Fixed cannot be maximized");
			return;
		}
		
		::glfwMaximizeWindow(m_window);
	}

	void CWindow::restore()
	{
		LOG_TRACE(U"CWindow::restore()");
		::glfwRestoreWindow(m_window);
	}

	void CWindow::minimize()
	{
		LOG_TRACE(U"CWindow::minimize()");
		::glfwIconifyWindow(m_window);
	}

	bool CWindow::setVirtualSize(const Size& size)
	{
		//LOG_TRACE(U"CWindow::setVirtualSize(size = {})"_fmt(size));

		const double scaling = m_state.scaling;
		const Size newFrameBufferSize = (size * scaling).asPoint();

		return setFrameBufferSize(newFrameBufferSize);
	}

	bool CWindow::setFrameBufferSize(const Size& size)
	{
		return(false);
	}

	void CWindow::setMinimumFrameBufferSize(const Size& size)
	{
		m_state.minFrameBufferSize = size;
	}
}
