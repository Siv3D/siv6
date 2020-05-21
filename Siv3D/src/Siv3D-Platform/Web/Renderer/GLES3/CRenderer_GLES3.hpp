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
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <Siv3D/Common.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>

namespace s3d
{
	class CRenderer_GLES3 final : public ISiv3DRenderer
	{
	private:
		
		GLFWwindow* m_window = nullptr;

	public:

		CRenderer_GLES3();

		~CRenderer_GLES3() override;

		void init() override;

		void onMainThreadStart() override;

		void clear() override;

		void flush() override;

		bool present() override;
	};
}
