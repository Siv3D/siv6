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

# include <Siv3D/Common.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CCursor.hpp"
# include <windowsx.h>

namespace s3d
{
	namespace detail
	{
		static void RegisterRawInput(HWND hWnd)
		{
			RAWINPUTDEVICE rid;
			rid.usUsagePage = 0x01; // HID_USAGE_PAGE_GENERIC;
			rid.usUsage		= 0x02; // HID_USAGE_GENERIC_MOUSE;
			rid.dwFlags		= RIDEV_INPUTSINK;
			rid.hwndTarget	= hWnd;

			LOG_TRACE(U"RegisterRawInputDevices()");
			if (!::RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE)))
			{
				LOG_FAIL(U"❌ RegisterRawInputDevices() failed");
			}
		}

		static Point GetCursorClientPos(HWND hWnd)
		{
			POINT screenPos;
			::GetCursorPos(&screenPos);
			POINT clientPos = screenPos;
			::ScreenToClient(hWnd, &clientPos);
			return{ clientPos.x, clientPos.y };
		}
	}

	CCursor::CCursor()
		: m_clientPosBuffer{ { Time::GetMicrosec(), Point(0, 0) } }
	{

	}

	CCursor::~CCursor()
	{
		LOG_SCOPED_TRACE(U"CCursor::~CCursor()");
	}

	void CCursor::init()
	{
		LOG_SCOPED_TRACE(U"CCursor::init()");

		m_hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());

		detail::RegisterRawInput(m_hWnd);

		{
			const Point clientPos = detail::GetCursorClientPos(m_hWnd);
			std::lock_guard lock(m_clientPosBufferMutex);
			m_clientPosBuffer.emplace_back(Time::GetMicrosec(), clientPos);
		}
		update();
	}

	bool CCursor::update()
	{
		Point lastClientPos;
		{
			const uint64 time = Time::GetMicrosec();
	
			std::lock_guard lock(m_clientPosBufferMutex);

			auto it = m_clientPosBuffer.begin();

			for (; it != (m_clientPosBuffer.end() - 1); ++it)
			{
				const uint64 elapsed = (time - it->first);

				if (elapsed < 1'000'000)
				{
					break;
				}
			}

			m_clientPosBuffer.erase(m_clientPosBuffer.begin(), it);

			lastClientPos = m_clientPosBuffer.back().second;
		}
		const double scaling = SIV3D_ENGINE(Window)->getState().scaling;
		m_state.update(lastClientPos, lastClientPos / scaling);

		return true;
	}

	const CursorState& CCursor::getState() const noexcept
	{
		return m_state;
	}

	void CCursor::handleMessage(const UINT message, const WPARAM, const LPARAM lParam)
	{
		Point newPosRaw;

		if (message == WM_MOUSEMOVE)
		{
			newPosRaw.set(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		}
		else if (message == WM_INPUT)
		{
			RAWINPUT raw;
			UINT rawSize = sizeof(raw);

			if (UINT resultData = ::GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, &raw, &rawSize, sizeof(RAWINPUTHEADER)); 
				resultData == UINT(-1))
			{
				return;
			}

			if (raw.header.dwType != RIM_TYPEMOUSE)
			{
				return;
			}

			newPosRaw = detail::GetCursorClientPos(m_hWnd);
		}
		else
		{
			return;
		}

		{
			std::lock_guard lock(m_clientPosBufferMutex);

			if (m_clientPosBuffer.back().second != newPosRaw)
			{
				m_clientPosBuffer.emplace_back(Time::GetMicrosec(), newPosRaw);
			}
		}
	}
}
