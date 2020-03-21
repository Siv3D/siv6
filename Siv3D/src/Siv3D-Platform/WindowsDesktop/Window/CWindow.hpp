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
# include <Siv3D/Window/IWindow.hpp>

namespace s3d
{
	class CWindow final : public ISiv3DWindow
	{
	private:

	public:

		CWindow();

		~CWindow() override;

		void init() override;
	};
}
