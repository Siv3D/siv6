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
# include "Formatter.hpp"
# include "PointVector.hpp"
# include "StringView.hpp"
# include "WindowStyle.hpp"

namespace s3d
{
	struct WindowState;

	namespace Window
	{
		inline constexpr Size DefaultClientSize = Size(800, 600);
		
		inline constexpr StringView DefaultTitle = U"Siv3D App";

		/// <summary>
		/// ウィンドウのタイトルを変更します。
		/// </summary>
		void SetTitle(const String& title);

		/// <summary>
		/// ウィンドウのタイトルを変更します。
		/// </summary>
	# if __cpp_lib_concepts
		template <Concept::Formattable... Args>
	# else
		template <class... Args>
	# endif
		inline void SetTitle(const Args&... args)
		{
			SetTitle(Format(args...));
		}

		/// <summary>
		/// 現在のウィンドウタイトルを返します。
		/// </summary>
		[[nodiscard]]
		const String& GetTitle() noexcept;

		[[nodiscard]]
		const WindowState& GetState() noexcept;

		void SetStyle(WindowStyle style);

		void SetMinimumFrameBufferSize(const Size& size);
	}
}
