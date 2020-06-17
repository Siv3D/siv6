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
# if  __has_include(<bit>)
#	include <bit>
# endif
# include "Common.hpp"

namespace s3d
{
	struct ColorF;
	struct HSV;

	struct Color
	{
		/// @brief 赤 | Red
		uint32 r : 8;

		/// @brief 緑 | Green
		uint32 g : 8;

		/// @brief 青 | Blue
		uint32 b : 8;

		/// @brief アルファ | Alpha
		uint32 a : 8;

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Color() = default;

		/// @brief コピーコンストラクタ
		SIV3D_NODISCARD_CXX20
		Color(const Color&) = default;

		SIV3D_NODISCARD_CXX20
		constexpr Color(uint32 _r, uint32 _g, uint32 _b, uint32 _a = 255) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Color(uint32 rgb, uint32 _a = 255) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Color(Color rgb, uint32 _a) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Color(const ColorF& color) noexcept;

		SIV3D_NODISCARD_CXX20
		Color(const HSV& hsv) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit Color(StringView code) noexcept;

		constexpr Color& operator =(const Color&) noexcept = default;

		constexpr Color& operator =(const ColorF& color) noexcept;

		Color& operator =(const HSV& hsv) noexcept;

		[[nodiscard]]
		constexpr Color operator ~() const noexcept;

		/// @brief 2 つの色が等しいかを返します。
		/// @param lhs 比較する色
		/// @param rhs 比較する色
		/// @return 2 つの色が等しい場合 true, それ以外の場合 false
		[[nodiscard]]
		friend constexpr bool operator ==(Color lhs, Color rhs) noexcept
		{
		# if __cpp_lib_is_constant_evaluated
			if (std::is_constant_evaluated()) // MSVC workaround
			{
				return (lhs.r == rhs.r)
					&& (lhs.g == rhs.g)
					&& (lhs.b == rhs.b)
					&& (lhs.a == rhs.a);
			}
			else
			{
			# if __cpp_lib_bit_cast
				return (std::bit_cast<uint32>(lhs) == std::bit_cast<uint32>(rhs));
			# else
				return (lhs.r == rhs.r)
					&& (lhs.g == rhs.g)
					&& (lhs.b == rhs.b)
					&& (lhs.a == rhs.a);
			# endif
			}
		# else
			# if __cpp_lib_bit_cast
				return (std::bit_cast<uint32>(lhs) == std::bit_cast<uint32>(rhs));
			# else
				return (lhs.r == rhs.r)
					&& (lhs.g == rhs.g)
					&& (lhs.b == rhs.b)
					&& (lhs.a == rhs.a);
			# endif
		# endif
		}

		[[nodiscard]]
		friend constexpr bool operator !=(Color lhs, Color rhs) noexcept
		{
		# if __cpp_lib_is_constant_evaluated
			if (std::is_constant_evaluated()) // MSVC workaround
			{
				return (lhs.r != rhs.r)
					|| (lhs.g != rhs.g)
					|| (lhs.b != rhs.b)
					|| (lhs.a != rhs.a);
			}
			else
			{
			# if __cpp_lib_bit_cast
				return (std::bit_cast<uint32>(lhs) != std::bit_cast<uint32>(rhs));
			# else
				return (lhs.r != rhs.r)
					|| (lhs.g != rhs.g)
					|| (lhs.b != rhs.b)
					|| (lhs.a != rhs.a);
			# endif
			}
		# else
			# if __cpp_lib_bit_cast
				return (std::bit_cast<uint32>(lhs) != std::bit_cast<uint32>(rhs));
			# else
			return (lhs.r != rhs.r)
				|| (lhs.g != rhs.g)
				|| (lhs.b != rhs.b)
				|| (lhs.a != rhs.a);
			# endif
		# endif
		}

		[[nodiscard]]
		static constexpr uint8 ToUint8(double x) noexcept;
	};
}
