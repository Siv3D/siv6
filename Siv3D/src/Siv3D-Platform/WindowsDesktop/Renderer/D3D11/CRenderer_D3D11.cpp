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

# include "CRenderer_D3D11.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CRenderer_D3D11::CRenderer_D3D11()
	{
	
	}

	CRenderer_D3D11::~CRenderer_D3D11()
	{
		LOG_SCOPED_TRACE(U"CRenderer_D3D11::~CRenderer_D3D11()");
	}

	void CRenderer_D3D11::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_D3D11::init()");
	}

	void CRenderer_D3D11::onMainThreadStart()
	{
		LOG_SCOPED_TRACE(U"CRenderer_D3D11::onMainThreadStart()");

		clear();
	}

	void CRenderer_D3D11::clear()
	{

	}

	void CRenderer_D3D11::flush()
	{

	}

	bool CRenderer_D3D11::present()
	{
		return true;
	}

	void CRenderer_D3D11::test_renderRectangle(const RectF&, const ColorF&)
	{

	}
}
