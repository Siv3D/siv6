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
	enum class EngineOption
	{
		/// @brief デバッグヒープマネージャ (Windows のみ)
		DebugHeap,

		/// @brief std::cerr の出力
		StdErr,

		/// @brief レンダラー
		Renderer,
	};

	enum class RendererType
	{
		/// @brief デフォルト
		PlatformDefault	= 0,

		/// @brief 非グラフィックスモード
		Headless		= 1,

		/// @brief OpenGL
		OpenGL			= 2,

		/// @brief Direc3D 11
		Direct3D11		= 3,
	};

	struct ApplicationOptions
	{
		bool debugHeap	= false;
		
		bool stdErr		= false;
		
		RendererType renderer	= RendererType::PlatformDefault;
	};

	namespace detail
	{
		int SetEngineOption(EngineOption, int) noexcept;
		int SetEngineOption(EngineOption, RendererType) noexcept;
	}

	extern ApplicationOptions g_applicationOptions;
}

# define SIV3D_COMBINE_(X,Y) X##Y
# define SIV3D_COMBINE(X,Y) SIV3D_COMBINE_(X,Y)
# define SIV3D_SET_OPTION(option,value) const int SIV3D_COMBINE(siv3d_engine_otpion_,__LINE__) = s3d::detail::SetEngineOption(##s3d::EngineOption::##option, value);
