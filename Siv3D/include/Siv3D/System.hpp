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
# include "Duration.hpp"

namespace s3d
{
	namespace System
	{
		/// <summary>
		/// 描画や入力情報など、フレームを更新します。
		/// </summary>
		/// <remarks>
		/// アプリケーション終了トリガーが発生するか、内部で回復不能なエラーが発生した場合に false を返します。この関数が false を返したらプログラムを終了させるべきです。
		/// </remarks>
		/// <returns>プログラムの続行の可否</returns>
		bool Update();

		/// <summary>
		/// プログラムを終了するために、この直後の `System::Update()` が false を返すように設定します。
		/// </summary>
		/// <remarks>
		/// この関数自体が終了処理を行うわけではないので、この関数の呼び出しは必須ではありません。
		/// </remarks>
		void Exit() noexcept;

		/// <summary>
		/// アプリケーション終了トリガーに設定するユーザアクションを設定します。
		/// </summary>
		/// <param name="userActionFlags">アプリケーション終了トリガーに設定するユーザアクションのフラグ</param>
		/// <remarks>
		/// フラグには `UserAction` の値の組み合わせを使います。
		/// </remarks>
		void SetTerminationTriggers(uint32 userActionFlags) noexcept;

		/// <summary>
		/// アプリケーション終了トリガーに設定したユーザアクションのフラグの現在の設定を返します。
		/// </summary>
		/// <remarks>
		/// フラグには `UserAction` の値の組み合わせが使われています。
		/// </remarks>
		/// <returns>アプリケーション終了トリガーに設定したユーザアクションのフラグ</returns>
		[[nodiscard]]
		uint32 GetTerminationTriggers() noexcept;

		/// <summary>
		/// 前回のフレームで発生したユーザアクションのフラグを返します。
		/// </summary>
		/// <remarks>
		/// フラグには `UserAction` の値の組み合わせが使われています。
		/// </remarks>
		/// <returns>前のフレームで発生したユーザアクションのフラグ</returns>
		[[nodiscard]]
		uint32 GetUserActions() noexcept;

		/// <summary>
		/// 現在のスレッドの実行を指定した時間だけ停止します。
		/// </summary>
		/// <param name="milliseconds">スリープする時間（ミリ秒）</param>
		void Sleep(int32 milliseconds);

		void Sleep(const Duration& duration);
	}
}
