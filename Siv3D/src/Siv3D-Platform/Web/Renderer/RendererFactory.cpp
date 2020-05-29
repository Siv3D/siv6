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

# include <Renderer/Null/CRenderer_Null.hpp>
# include <Renderer/GLES3/CRenderer_GLES3.hpp>
# include <Siv3D/Common/ApplicationOptions.hpp>

namespace s3d
{
	ISiv3DRenderer* ISiv3DRenderer::Create()
	{
		if (g_ApplicationOptions.headlessMode)
		{
			return new CRenderer_Null;
		}
		else
		{
			return new CRenderer_GLES3;
		}
	}
}
