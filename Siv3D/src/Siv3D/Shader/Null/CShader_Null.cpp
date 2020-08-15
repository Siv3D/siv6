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

# include "CShader_Null.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CShader_Null::CShader_Null()
	{

	}

	CShader_Null::~CShader_Null()
	{
		LOG_SCOPED_TRACE(U"CShader_Null::~CShader_Null()");
	}

	void CShader_Null::init()
	{
		LOG_SCOPED_TRACE(U"CShader_Null::init()");

	}

	bool CShader_Null::update()
	{
		return true;
	}
}
