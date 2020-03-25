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

# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/UserAction/IUserAction.hpp>
# include "CSystem.hpp"

namespace s3d
{
	CSystem::CSystem()
	{

	}

	CSystem::~CSystem()
	{

	}

	void CSystem::init()
	{
		SIV3D_ENGINE(Window)->init();
	}

	bool CSystem::update()
	{
		if (SIV3D_ENGINE(UserAction)->terminationTriggered())
		{
			return false;
		}
		
		SIV3D_ENGINE(Window)->update();
		
		return true;
	}
}
