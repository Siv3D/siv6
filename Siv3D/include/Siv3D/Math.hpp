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
	//////////////////////////////////////////////////
	//
	//	Square
	//
	//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 平方を計算します。
		/// </summary>
		[[nodiscard]]
		inline constexpr float Square(float x) noexcept
		{
			return (x * x);
		}

		/// <summary>
		/// 平方を計算します。
		/// </summary>
		[[nodiscard]]
		inline constexpr double Square(double x) noexcept
		{
			return (x * x);
		}

		/// <summary>
		/// 平方を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]]
		inline constexpr Type Square(Type x) noexcept
		{
			return (x * x);
		}
	}

	namespace detail
	{
		struct Square_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Square(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Square_impl();
			}
		};
	}

	constexpr auto Square = detail::Square_impl();
}
