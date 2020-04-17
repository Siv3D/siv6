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
# include <array>
# include <random>
# include "Types.hpp"

namespace s3d
{
	/// <summary>
	/// 乱数生成エンジン
	/// </summary>
	class HardwareRNG
	{
	private:

		using engine_type = std::random_device;

		engine_type m_engine;

	public:

		using result_type = engine_type::result_type;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		HardwareRNG() = default;

		/// <summary>
		/// 生成される乱数の最小値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最小値
		/// </returns>
		[[nodiscard]]
		static constexpr result_type min() noexcept
		{
			return engine_type::min();
		}

		/// <summary>
		/// 生成される乱数の最大値を返します。
		/// </summary>
		/// <returns>
		/// 生成される乱数の最大値
		/// </returns>
		[[nodiscard]]
		static constexpr result_type max() noexcept
		{
			return engine_type::max();
		}

		/// <summary>
		/// 乱数を生成します。
		/// </summary>
		/// <returns>
		/// 乱数
		/// </returns>
		result_type operator()()
		{
			return m_engine();
		}

		template <size_t N>
		std::array<result_type, N> generateSeeds() noexcept
		{
			std::array<result_type, N> seeds;

			for (auto& seed : seeds)
			{
				seed = m_engine();
			}

			return seeds;
		}
	};
}
