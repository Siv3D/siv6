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
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <Siv3D/Renderer/IRenderer.hpp>

namespace s3d
{
	class CRenderer_GL4 final : public ISiv3DRenderer
	{
	private:
		
		GLFWwindow* m_window = nullptr;

		Size m_frameBufferSize = Size(0, 0);

	public:

		CRenderer_GL4();

		~CRenderer_GL4() override;

		void init() override;

		void onMainThreadStart() override;

		void clear() override;

		void flush() override;

		bool present() override;

		void test_renderRectangle(const RectF& rect, const ColorF& color) override;
	};
}
