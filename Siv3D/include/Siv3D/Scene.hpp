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
# include "Common.hpp"
# include "PointVector.hpp"
# include "Window.hpp"

namespace s3d
{
	namespace Scene
	{
		/// <summary>
		/// シーンの幅と高さ（ピクセル）のデフォルト値です。
		/// </summary>
		inline constexpr s3d::Size DefaultSceneSize = Window::DefaultClientSize;

		/// <summary>
		/// `System::Update()` が呼ばれた回数（= フレームカウント）を返します。
		/// </summary>
		/// <remarks>
		/// ユーザの環境によってフレームレートが変わるため、この値をアニメーション等の制御に使ってはいけません。
		/// </remarks>
		/// <returns>`System::Update()` が呼ばれた回数</returns>
		[[nodiscard]]
		int32 FrameCount() noexcept;
	}
}
