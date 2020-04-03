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

# include "CRenderer_GL4.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	CRenderer_GL4::CRenderer_GL4()
	{
	
	}

	CRenderer_GL4::~CRenderer_GL4()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GL4::~CRenderer_GL4()");
	}

	void CRenderer_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GL4::init()");
	}

	void CRenderer_GL4::onMainThreadStart()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GL4::onMainThreadStart()");

		clear();
	}

	void CRenderer_GL4::clear()
	{

	}

	void CRenderer_GL4::flush()
	{

	}

	bool CRenderer_GL4::present()
	{
		return true;
	}
}
