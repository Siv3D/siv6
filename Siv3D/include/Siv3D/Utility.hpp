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
# include <algorithm>
# include <type_traits>
# include "Common.hpp"
# include "PlaceHolder.hpp"

namespace s3d
{
	//////////////////////////////////////////////////
	//
	//	Max
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		template <class Type>
		struct Max1_impl
		{
			const Type& a;

			constexpr Max1_impl(const Type& _a) noexcept
				: a(_a) {}

			[[nodiscard]]
			constexpr const Type& operator()(const Type& b) const noexcept(noexcept(a < b))
			{
				return (a < b) ? b : a;
			}
		};

		struct Max2_impl
		{
		# if __cpp_lib_concepts
			template <Concept::Scalar Type>
		# else
			template <class Type, std::enable_if_t<std::is_scalar_v<Type>>* = nullptr>
		# endif
			[[nodiscard]]
			constexpr Type operator()(Type a, Type b) const noexcept
			{
				return (a < b) ? b : a;
			}

		# if __cpp_lib_concepts
			template <class Type>
		# else
			template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
		# endif
			[[nodiscard]]
			constexpr const Type& operator()(const Type& a, const Type& b) const noexcept(noexcept(a < b))
			{
				return (a < b) ? b : a;
			}
		};
	}

	template <class Type>
	[[nodiscard]]
	inline constexpr auto Max(const Type& a, PlaceHolder_t) noexcept
	{
		return detail::Max1_impl<Type>(a);
	}

	template <class Type>
	[[nodiscard]]
	inline constexpr auto Max(PlaceHolder_t, const Type& b) noexcept
	{
		return detail::Max1_impl<Type>(b);
	}

	[[nodiscard]]
	inline constexpr auto Max(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::Max2_impl();
	}

	/// <summary>
	/// 2 つの値のうち大きい方の値を返します。
	/// Returns the greater of the two.
	/// </summary>
	/// <param name="a">
	/// 比較する値
	/// A value to compare
	/// </param>
	/// <param name="b">
	/// 比較する値
	/// Another value to compare
	/// </param>
	/// <returns>
	/// 2 つの値のうち大きい方の値。等しい場合は a
	/// The greater of a and b. If they are equivalent, returns a
	/// </returns>
# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr Type Max(Type a, Type b) noexcept
	{
		return (a < b) ? b : a;
	}

# if __cpp_lib_concepts
	template <class Type>
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr const Type& Max(const Type& a, const Type& b) noexcept(noexcept(a < b))
	{
		return (a < b) ? b : a;
	}

	/// <summary>
	/// 渡された初期化リストの中で最大の値を返します。
	/// Returns the greatest of the values in initializer list.
	/// </summary>
	/// <param name="ilist">
	/// 比較する値の初期化リスト
	/// Initializer list with the values to compare 
	/// </param>
	/// <returns>
	/// 初期化リストの中で最大の値。複数が等しい場合はその中で最も左の値
	/// The greatest value in ilist. If several values are equivalent to the greatest, returns the leftmost one
	/// </returns>
	template <class Type>
	[[nodiscard]]
	inline constexpr Type Max(std::initializer_list<Type> ilist)
	{
		return *std::max_element(ilist.begin(), ilist.end());
	}

	//////////////////////////////////////////////////
	//
	//	Min
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		template <class Type>
		struct Min1_impl
		{
			const Type& a;

			constexpr Min1_impl(const Type& _a) noexcept
				: a(_a) {}

			[[nodiscard]]
			constexpr const Type& operator()(const Type& b) const noexcept(noexcept(b < a))
			{
				return (b < a) ? b : a;
			}
		};

		struct Min2_impl
		{
		# if __cpp_lib_concepts
			template <Concept::Scalar Type>
		# else
			template <class Type, std::enable_if_t<std::is_scalar_v<Type>>* = nullptr>
		# endif
			[[nodiscard]]
			constexpr Type operator()(Type a, Type b) const noexcept
			{
				return (b < a) ? b : a;
			}

		# if __cpp_lib_concepts
			template <class Type>
		# else
			template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
		# endif
			[[nodiscard]]
			constexpr const Type& operator()(const Type& a, const Type& b) const noexcept(noexcept(b < a))
			{
				return (b < a) ? b : a;
			}
		};
	}

	template <class Type>
	[[nodiscard]]
	inline constexpr auto Min(const Type& a, PlaceHolder_t) noexcept
	{
		return detail::Min1_impl<Type>(a);
	}

	template <class Type>
	[[nodiscard]]
	inline constexpr auto Min(PlaceHolder_t, const Type& b) noexcept
	{
		return detail::Min1_impl<Type>(b);
	}

	[[nodiscard]]
	inline constexpr auto Min(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::Min2_impl();
	}

	/// <summary>
	/// 2 つの値のうち小さい方の値を返します。
	/// Returns the lesser of the two.
	/// </summary>
	/// <param name="a">
	/// 比較する値
	/// A value to compare
	/// </param>
	/// <param name="b">
	/// 比較する値
	/// Another value to compare
	/// </param>
	/// <returns>
	/// 2 つの値のうち小さい方の値。等しい場合は a
	/// The greater of a and b. If they are equivalent, returns a
	/// </returns>
# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr Type Min(Type a, Type b) noexcept
	{
		return (b < a) ? b : a;
	}

	/// <summary>
	/// 2 つの値のうち小さい方の値を返します。
	/// Returns the lesser of the two.
	/// </summary>
	/// <param name="a">
	/// 比較する値
	/// A value to compare
	/// </param>
	/// <param name="b">
	/// 比較する値
	/// Another value to compare
	/// </param>
	/// <returns>
	/// 2 つの値のうち小さい方の値。等しい場合は a
	/// The greater of a and b. If they are equivalent, returns a
	/// </returns>
# if __cpp_lib_concepts
	template <class Type>
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr const Type& Min(const Type& a, const Type& b) noexcept(noexcept(b < a))
	{
		return (b < a) ? b : a;
	}

	/// <summary>
	/// 渡された初期化リストの中で最小の値を返します。
	/// Returns the least of the values in initializer list.
	/// </summary>
	/// <param name="ilist">
	/// 比較する値の初期化リスト
	/// Initializer list with the values to compare 
	/// </param>
	/// <returns>
	/// 初期化リストの中で最小大の値。複数が等しい場合はその中で最も左の値
	/// The least value in ilist. If several values are equivalent to the least, returns the leftmost one
	/// </returns>
	template <class Type>
	[[nodiscard]]
	inline constexpr Type Min(std::initializer_list<Type> ilist)
	{
		return *std::min_element(ilist.begin(), ilist.end());
	}

	//////////////////////////////////////////////////
	//
	//	Clamp
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		template <class Type>
		class Clamp_impl
		{
		private:

			const Type& min;

			const Type& max;

		public:

			constexpr Clamp_impl(const Type& _min, const Type& _max) noexcept
				: min(_min)
				, max(_max) {}

			[[nodiscard]]
			constexpr const Type& operator()(const Type& v) const noexcept(noexcept(max < v) && noexcept(v < min))
			{
				if (max < v)
				{
					return max;
				}

				if (v < min)
				{
					return min;
				}

				return v;
			}
		};
	}

	template <class Type>
	[[nodiscard]] constexpr auto Clamp(PlaceHolder_t, const Type& min, const Type& max) noexcept
	{
		return detail::Clamp_impl<Type>(min, max);
	}

	/// <summary>
	/// 最小値と最大値の範囲にクランプした値を返します。
	/// Clamps the value to the specified minimum and maximum range
	/// </summary>
	/// <param name="v">
	/// クランプする値
	/// A value to clamp
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// The specified minimum range
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// The specified maximum range
	/// </param>
	/// <returns>
	/// v をクランプした値
	/// The clamped value for the v
	/// </returns>
# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr Type Clamp(Type v, Type min, Type max) noexcept
	{
		if (max < v)
		{
			return max;
		}

		if (v < min)
		{
			return min;
		}

		return v;
	}

# if __cpp_lib_concepts
	template <class Type>
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr const Type& Clamp(const Type& v, const Type& min, const Type& max) noexcept(noexcept(max < v) && noexcept(v < min))
	{
		if (max < v)
		{
			return max;
		}

		if (v < min)
		{
			return min;
		}

		return v;
	}

	//////////////////////////////////////////////////
	//
	//	InRange
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		template <class Type>
		class InRange_impl
		{
		private:

			const Type& min;

			const Type& max;

		public:

			constexpr InRange_impl(const Type& _min, const Type& _max) noexcept
				: min(_min)
				, max(_max) {}

			[[nodiscard]]
			constexpr bool operator()(const Type& v) const noexcept(noexcept(min <= v))
			{
				return (min <= v) && (v <= max);
			}
		};
	}

	template <class Type>
	[[nodiscard]]
	inline constexpr auto InRange(PlaceHolder_t, const Type& min, const Type& max) noexcept
	{
		return detail::InRange_impl<Type>(min, max);
	}

	/// <summary>
	/// 値が閉区間 [min, max] にあるかを返します。
	/// Returns true if the value is in the closed interval [min, max]
	/// </summary>
	/// <param name="v">
	/// 調べる値
	/// A value
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// The specified minimum range
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// The specified maximum range
	/// </param>
	/// <returns>
	/// 閉区間 [min, max] にある場合 true, それ以外の場合は false
	/// Returns true if the value is in the closed interval [min, max], false otherwise
	/// </returns>
# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr bool InRange(Type v, Type min, Type max) noexcept
	{
		return (min <= v) && (v <= max);
	}

	/// <summary>
	/// 値が閉区間 [min, max] にあるかを返します。
	/// Returns true if the value is in the closed interval [min, max]
	/// </summary>
	/// <param name="v">
	/// 調べる値
	/// A value
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// The specified minimum range
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// The specified maximum range
	/// </param>
	/// <returns>
	/// 閉区間 [min, max] にある場合 true, それ以外の場合は false
	/// Returns true if the value is in the closed interval [min, max], false otherwise
	/// </returns>
# if __cpp_lib_concepts
	template <class Type>
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr bool InRange(const Type& v, const Type& min, const Type& max) noexcept(noexcept(v < min))
	{
		return (min <= v) && (v <= max);
	}

	//////////////////////////////////////////////////
	//
	//	InOpenRange
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		template <class Type>
		class InOpenRange_impl
		{
		private:

			const Type& min;

			const Type& max;

		public:

			constexpr InOpenRange_impl(const Type& _min, const Type& _max) noexcept
				: min(_min)
				, max(_max) {}

			[[nodiscard]]
			constexpr bool operator()(const Type& v) const noexcept(noexcept(min < v))
			{
				return (min < v) && (v < max);
			}
		};
	}

	template <class Type>
	[[nodiscard]]
	inline constexpr auto InOpenRange(PlaceHolder_t, const Type& min, const Type& max) noexcept
	{
		return detail::InOpenRange_impl<Type>(min, max);
	}

	/// <summary>
	/// 値が開区間 (min, max) にあるかを返します。
	/// Returns true if the value is in the open interval (min, max)
	/// </summary>
	/// <param name="v">
	/// 調べる値
	/// A value
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// The specified minimum range
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// The specified maximum range
	/// </param>
	/// <returns>
	/// 開区間 (min, max) にある場合 true, それ以外の場合は false
	/// Returns true if the value is in the open interval (min, max), false otherwise
	/// </returns>
# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr bool InOpenRange(Type v, Type min, Type max) noexcept
	{
		return (min < v) && (v < max);
	}

	/// <summary>
	/// 値が開区間 (min, max) にあるかを返します。
	/// Returns true if the value is in the open interval (min, max)
	/// </summary>
	/// <param name="v">
	/// 調べる値
	/// A value
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// The specified minimum range
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// The specified maximum range
	/// </param>
	/// <returns>
	/// 開区間 (min, max) にある場合 true, それ以外の場合は false
	/// Returns true if the value is in the open interval (min, max), false otherwise
	/// </returns>
# if __cpp_lib_concepts
	template <class Type>
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
# endif
	[[nodiscard]]
	inline constexpr bool InOpenRange(const Type& v, const Type& min, const Type& max) noexcept(noexcept(v < min))
	{
		return (min < v) && (v < max);
	}

	namespace detail
	{
		struct FromEnum_impl
		{
		# if __cpp_lib_concepts
			template <Concept::Enum Enum>
		# else
			template <class Enum, std::enable_if_t<std::is_enum_v<Enum>>* = nullptr>
		# endif
			[[nodiscard]]
			constexpr auto operator ()(Enum x) const noexcept
			{
				return static_cast<std::underlying_type_t<Enum>>(x);
			}

			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return FromEnum_impl();
			}
		};
	}

	inline constexpr auto FromEnum = detail::FromEnum_impl();

	namespace detail
	{
	# if __cpp_lib_concepts
		template <Concept::Enum Enum>
	# else
		template <class Enum, std::enable_if_t<std::is_enum_v<Enum>>* = nullptr>
	# endif
		struct ToEnum_impl
		{
			[[nodiscard]]
			constexpr auto operator ()(std::underlying_type_t<Enum> x) const noexcept
			{
				return Enum{ x };
			}

			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return ToEnum_impl();
			}
		};
	}

# if __cpp_lib_concepts
	template <Concept::Enum Enum>
# else
	template <class Enum, std::enable_if_t<std::is_enum_v<Enum>>* = nullptr>
# endif
	inline constexpr auto ToEnum = detail::ToEnum_impl<Enum>();
}
