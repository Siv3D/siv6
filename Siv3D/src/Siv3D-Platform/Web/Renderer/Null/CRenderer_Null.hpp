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
# include <Siv3D/Renderer/IRenderer.hpp>

namespace s3d
{
	class CRenderer_Null final : public ISiv3DRenderer
	{
	private:

	public:

		CRenderer_Null();

		~CRenderer_Null() override;

		void init() override;

		void onMainThreadStart() override;

		void clear() override;

		void flush() override;

		bool present() override;
	};
}
