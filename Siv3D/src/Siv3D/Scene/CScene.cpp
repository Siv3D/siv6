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

# include "CScene.hpp"

namespace s3d
{
	void CScene::update()
	{
		++m_systemFrameCount;
		++m_userFrameCount;
	}

	int32 CScene::getFrameCount() const noexcept
	{
		return m_userFrameCount;
	}
}
