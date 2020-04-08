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
	/// <summary>
	/// コピー禁止 Mixin
	/// Non-copyable mixin
	/// </summary>
	/// <remarks>
	/// このクラスを private 継承して使います。
	/// Intended to be used as a private base class.
	/// </remarks>
	class Uncopyable
	{
	protected:

		Uncopyable() = default;

		~Uncopyable() = default;

		Uncopyable(const Uncopyable&) = delete;

		Uncopyable& operator =(const Uncopyable&) = delete;
	};
}
