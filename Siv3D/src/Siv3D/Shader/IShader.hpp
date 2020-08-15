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

# pragma once
# include <Siv3D/Common.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DShader
	{
	public:

		static ISiv3DShader* Create();

		virtual ~ISiv3DShader() = default;

		virtual void init() = 0;

		virtual bool update() = 0;
	};
}
