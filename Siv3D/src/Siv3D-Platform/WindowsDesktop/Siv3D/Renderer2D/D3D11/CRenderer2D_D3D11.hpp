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

namespace s3d
{
	class CRenderer2D_D3D11 final : public ISiv3DRenderer2D
	{
	private:

		CRenderer_D3D11* pRenderer		= nullptr;

		ID3D11Device* m_device			= nullptr;

		ID3D11DeviceContext* m_context	= nullptr;

	public:

		CRenderer2D_D3D11();

		~CRenderer2D_D3D11() override;

		void init() override;

		void flush() override;

		void test_renderRectangle(const RectF& rect, const ColorF& color) override;

		void drawFullScreenTriangle(TextureFilter textureFilter) override;
	};
}
