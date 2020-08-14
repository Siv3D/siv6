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

# include <Siv3D/Scene.hpp>
# include <Siv3D/Scene/IScene.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Scene
	{
		int32 FrameCount() noexcept
		{
			return SIV3D_ENGINE(Scene)->getFrameCount();
		}

		void SetResizeMode(const ResizeMode resizeMode)
		{
			return SIV3D_ENGINE(Renderer)->setSceneResizeMode(resizeMode);
		}
	}
}
