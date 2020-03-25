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

namespace s3d
{
	/// <summary>
	/// アプリケーションを終了させるためのユーザアクションを表します。
	/// User Actions for Application Termination
	/// </summary>
	/// <remarks>
	/// System::SetTerminationTriggers(), System::GetTerminationTriggers(), System::GetUserActions() で使われる定数
	/// | 演算子で複数の値を組み合わせることができます。
	/// Constants used for System::SetTerminationTriggers(), System::GetTerminationTriggers(), and System::GetUserActions()
	/// </remarks>
	namespace UserAction
	{
		enum Flag : uint32
		{
			/// <summary>
			/// アプリケーションウィドウの閉じるボタンを押す操作です。
			/// The user has clicked the close button of the application window.
			/// </summary>
			CloseButtonClicked = 0b000001u,

			/// <summary>
			/// エスケープキーを押す操作です。
			/// The user has pressed the escape key.
			/// </summary>
			EscapeKeyDown = 0b000010u,

			/// <summary>
			/// ウィンドウを非アクティブにする操作です。
			/// The application window has been deactivated.
			/// </summary>
			WindowDeactivated = 0b000100u,

			/// <summary>
			/// 何らかのキーを押す操作です。
			/// The user has pressed a key.
			/// </summary>
			AnyKeyDown = 0b001000u,

			/// <summary>
			/// 何らかのマウスのボタンを押す操作です。
			/// The user has pressed a mouse button.
			/// </summary>
			MouseButtonDown = 0b010000u,

			/// <summary>
			/// 何らかのキー、または何らかのマウスのボタンを押す操作です。
			/// The user has pressed a key or a mouse button.
			/// </summary>
			AnyKeyOrMouseDown = (AnyKeyDown | MouseButtonDown),

			/// <summary>
			/// アプリケーションウィドウの閉じるボタンを押すか、エスケープキーを押す操作です。
			/// Default (CloseButtonClicked | EscapeKeyDown)
			/// </summary>
			Default = (CloseButtonClicked | EscapeKeyDown),

			/// <summary>
			/// アプリケーションを終了させるためのユーザアクションを設定しないことを示します。
			/// None
			/// </summary>
			/// <remarks>
			/// System::SetTerminationTriggers() にこの定数のみを渡した場合、メインループから抜けるには break や return を使うか、System::Exit() を呼ぶ必要があります。
			/// When this flag is set exclusively, you must explicitly call System::Exit() to exit the main loop.
			/// </remarks>
			None = 0u,
		};
	};
}
