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

		clear();
	}

	StringView CRenderer_D3D11::getName() const
	{
		static constexpr StringView name(U"D3D11");
		return name;
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

	Size CRenderer_D3D11::getFrameBufferSize() const
	{
		return(Size(0, 0));
	}

	Size CRenderer_D3D11::getSceneSize() const
	{
		return(Size(0, 0));
	}
}
