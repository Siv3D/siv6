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

namespace s3d
{
	enum class RendererType
	{
		PlatformDefault = 0,
		OpenGL = 1,
		Direct3D11 = 2,
	};
}

# include "detail/ApplicationOptions.ipp"

/// @brief デバッグヒープマネージャ (Windows のみ)
# define SIV3D_OPTION_DEBUG_HEAP_MANAGER(bool) const int dummy_s3d_enable_debug_heap_manager = s3d::detail::EnableDebugHeapManager(bool)

/// @brief 非グラフィックスモード
# define SIV3D_OPTION_HEADLESS_MODE(bool) const int dummy_s3d_enable_headless_mode = s3d::detail::EnableHeadlessMode(bool)

/// @brief std::cerr の出力
# define SIV3D_OPTION_OUTPUT_STDERR(bool) const int dummy_s3d_enable_stderr = s3d::detail::EnableStdErr(bool)

/// @brief テストの実行
# define SIV3D_OPTION_RUN_TEST(bool) const int dummy_s3d_enable_test = s3d::detail::EnableTest(bool)

/// @brief レンダラー
# define SIV3D_OPTION_RENDERER(RendererType) const int dummy_s3d_renderer = s3d::detail::SetRenderer(RendererType)
