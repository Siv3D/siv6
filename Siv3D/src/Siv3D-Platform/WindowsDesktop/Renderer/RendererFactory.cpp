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
# include <Renderer/GL4/CRenderer_GL4.hpp>
# include <Renderer/D3D11/CRenderer_D3D11.hpp>
# include <Siv3D/Common/ApplicationOptions.hpp>

namespace s3d
{
	ISiv3DRenderer* ISiv3DRenderer::Create()
	{
		if (g_ApplicationOptions.headlessMode)
		{
			return new CRenderer_Null;
		}
		
		if (g_ApplicationOptions.renderer == RendererType::PlatformDefault
			|| g_ApplicationOptions.renderer == RendererType::Direct3D11)
		{
			return new CRenderer_D3D11;
		}
		else
		{
			return new CRenderer_GL4;
		}
	}
}
