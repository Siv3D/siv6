//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Console.hpp>
# include <Console/IConsole.hpp>
# include <Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		void Console_impl::open() const
		{
			Siv3DEngine::Get<ISiv3DConsole>()->open();
		}
	}
}
