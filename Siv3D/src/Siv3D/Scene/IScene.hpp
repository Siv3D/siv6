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
	class ISiv3DScene
	{
	public:

		static ISiv3DScene* Create();

		virtual ~ISiv3DScene() = default;

		virtual void update() = 0;

		virtual int32 getFrameCount() const noexcept = 0;
	};
}
