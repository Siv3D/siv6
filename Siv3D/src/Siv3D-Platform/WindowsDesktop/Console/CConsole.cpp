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
# include <Siv3D/Common/ApplicationOptions.hpp>
# include "CConsole.hpp"

namespace s3d
{
	CConsole::CConsole()
	{

	}

	CConsole::~CConsole()
	{
		close();
	}

	void CConsole::open()
	{
		if (m_isOpen)
		{
			return;
		}

		::AllocConsole();
		::freopen_s(&m_fpOut, "CONOUT$", "w", stdout);
		::freopen_s(&m_fpIn, "CONIN$", "r", stdin);
		if (g_ApplicationOptions.stdErr)
		{
			::freopen_s(&m_fpErr, "CONOUT$", "w", stderr);
		}

		m_isOpen = true;
	}

	void CConsole::close()
	{
		if (!m_isOpen)
		{
			return;
		}

		if (m_fpErr)
		{
			::fclose(m_fpErr);
			m_fpErr = nullptr;
		}

		if (m_fpIn)
		{
			::fclose(m_fpIn);
			m_fpIn = nullptr;
		}

		if (m_fpOut)
		{
			::fclose(m_fpOut);
			m_fpOut = nullptr;
		}

		::FreeConsole();
	}
}
