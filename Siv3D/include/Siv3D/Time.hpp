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
# include "Fwd.hpp"

namespace s3d
{
	/// <summary>
	/// 時間
	/// </summary>
	/// <remarks>
	/// 時間に関する機能を提供します。
	/// </remarks>
	namespace Time
	{
		/// <summary>
		/// コンピューターが起動してからの経過時間を秒で返します。
		/// </summary>
		/// <returns>
		/// コンピューターが起動してからの経過時間（秒）
		/// </returns>
		[[nodiscard]]
		uint64 GetSec() noexcept;

		/// <summary>
		/// コンピューターが起動してからの経過時間をミリ秒で返します。
		/// </summary>
		/// <returns>
		/// コンピューターが起動してからの経過時間（ミリ秒）
		/// </returns>
		[[nodiscard]]
		uint64 GetMillisec() noexcept;

		/// <summary>
		/// コンピューターが起動してからの経過時間をマイクロ秒で返します。
		/// </summary>
		/// <returns>
		/// コンピューターが起動してからの経過時間（マイクロ秒）
		/// </returns>
		[[nodiscard]]
		uint64 GetMicrosec() noexcept;

		/// <summary>
		/// コンピューターが起動してからの経過時間をナノ秒で返します。
		/// </summary>
		/// <returns>
		/// コンピューターが起動してからの経過時間（ナノ秒）
		/// </returns>
		[[nodiscard]]
		uint64 GetNanosec() noexcept;
	}
}
