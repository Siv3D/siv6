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
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Renderer/D3D11/CRenderer_D3D11.hpp>
# include <Siv3D/Shader/D3D11/CShader_D3D11.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>

namespace s3d
{
	struct D3D11StandardVS2D
	{
		VertexShader fullscreen_triangle;

		bool ok() const
		{
			return !!fullscreen_triangle;
		}
	};

	struct D3D11StandardPS2D
	{
		PixelShader fullscreen_triangle;

		bool setup()
		{
			return !!fullscreen_triangle;
		}
	};

	class CRenderer2D_D3D11 final : public ISiv3DRenderer2D
	{
	private:

		CRenderer_D3D11* pRenderer		= nullptr;

		CShader_D3D11* pShader			= nullptr;

		ID3D11Device* m_device			= nullptr;

		ID3D11DeviceContext* m_context	= nullptr;

		std::unique_ptr<D3D11StandardVS2D> m_standardVS;

		std::unique_ptr<D3D11StandardPS2D> m_standardPS;

	public:

		CRenderer2D_D3D11();

		~CRenderer2D_D3D11() override;

		void init() override;

		void flush() override;

		void test_renderRectangle(const RectF& rect, const ColorF& color) override;

		void drawFullScreenTriangle(TextureFilter textureFilter) override;
	};
}
