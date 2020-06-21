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

# include "CRenderer_Null.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CRenderer_Null::CRenderer_Null()
	{
	
	}

	CRenderer_Null::~CRenderer_Null()
	{
		LOG_SCOPED_TRACE(U"CRenderer_Null::~CRenderer_Null()");
	}

	void CRenderer_Null::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_Null::init()");
		
		clear();
	}

	void CRenderer_Null::clear()
	{

	}

	void CRenderer_Null::flush()
	{

	}

	bool CRenderer_Null::present()
	{
		return true;
	}

	void CRenderer_Null::test_renderRectangle(const RectF&, const ColorF&)
	{

	}
}
