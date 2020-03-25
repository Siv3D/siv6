﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/System.hpp>
# include <Siv3D/System/ISystem.hpp>
# include <Siv3D/UserAction/IUSerAction.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace System
	{
		bool Update()
		{
			return SIV3D_ENGINE(System)->update();
		}

		void Exit() noexcept
		{
			SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::SystemExitCalled);
		}
	}
}
