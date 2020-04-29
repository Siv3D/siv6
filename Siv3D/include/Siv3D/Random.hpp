﻿//-----------------------------------------------
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
# include "SMFT.hpp"

namespace s3d
{
	using DefaultRNG_t = PRNG::SFMT19937_64;

	[[nodiscard]]
	DefaultRNG_t& GetDefaultRNG() noexcept;

	void Reseed(uint64 seed) noexcept;

	void Reseed(const std::array<uint64, 16>& seeds) noexcept;

	/// <summary>
	/// [0, 1) の範囲の乱数を返します。
	/// </summary>
	/// <remarks>
	/// グローバルな乱数エンジンを使用します。
	/// </remarks>
	/// <returns>
	/// [0, 1) の範囲の乱数
	/// </returns>
	double Random() noexcept;
}