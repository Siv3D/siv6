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
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>

namespace s3d
{
	class CRenderer_GL4 final : public ISiv3DRenderer
	{
	private:

		HWND m_hWnd = nullptr;
		HDC m_hDC = nullptr;
		HGLRC m_glContext = nullptr;

	public:

		CRenderer_GL4();

		~CRenderer_GL4() override;

		void init() override;
	};
}
