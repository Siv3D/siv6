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
# include "SMFT.hpp"
# include "Distribution.hpp"

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

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic>
# else
	template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>* = nullptr>
# endif
	inline Arithmetic Random(Arithmetic min, Arithmetic max);

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic>
# else
	template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>* = nullptr>
# endif
	inline Arithmetic Random(Arithmetic max);

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic>
# else
	template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>* = nullptr>
# endif
	inline Arithmetic RandomOpen(Arithmetic min, Arithmetic max);

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic>
# else
	template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>* = nullptr>
# endif
	inline Arithmetic RandomClosed(Arithmetic min, Arithmetic max);

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic>
# else
	template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>* = nullptr>
# endif
	inline Arithmetic RandomOpenClosed(Arithmetic min, Arithmetic max);

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic>
# else
	template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>* = nullptr>
# endif
	inline Arithmetic RandomClosedOpen(Arithmetic min, Arithmetic max);

	inline bool RandomBool(double p = 0.5) noexcept;

	inline uint8 RandomUint8();

	inline uint16 RandomUint16();

	inline uint32 RandomUint32();

	inline uint64 RandomUint64();

	inline int8 RandomInt8();

	inline int16 RandomInt16();

	inline int32 RandomInt32();

	inline int64 RandomInt64();
}

# include "detail/Random.ipp"
