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

# pragma once
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Optional.hpp>
# include "Monitor.hpp"

namespace s3d
{
	class CWindow_Null final : public ISiv3DWindow
	{
	private:

		HINSTANCE m_hInstance = nullptr;

		HMODULE m_user32 = nullptr;
		decltype(GetSystemMetricsForDpi)* m_pGetSystemMetricsForDpi = nullptr;
		decltype(AdjustWindowRectExForDpi)* m_pAdjustWindowRectExForDpi = nullptr;

		String m_title = String(Window::DefaultTitle);

		WindowState m_state;

	public:

		CWindow_Null();

		~CWindow_Null() override;

		void init() override;

		void destroy() override;

		void update() override;

		void setWindowTitle(const String& title) override;

		const String& getWindowTitle() const noexcept override;

		void* getHandle() const noexcept override;

		const WindowState& getState() const noexcept override;

		void setStyle(WindowStyle style) override;

		void setPos(const Point& pos) override;

		void maximize() override;

		void restore() override;

		void minimize() override;

		bool setVirtualSize(const Size& size) override;

		bool setFrameBufferSize(const Size& size) override;

		void setMinimumFrameBufferSize(const Size& size) override;
	};
}
