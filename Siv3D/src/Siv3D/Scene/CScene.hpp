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
# include "IScene.hpp"

namespace s3d
{
	class CScene final : public ISiv3DScene
	{
	private:

		uint64 m_systemFrameCount = 0;

		int32 m_userFrameCount = 0;

	public:

		void update() override;

		int32 getFrameCount() const noexcept override;
	};
}
