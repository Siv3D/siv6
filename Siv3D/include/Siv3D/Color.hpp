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
# include "FormatData.hpp"
# include "FormatLiteral.hpp"

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

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Color& value)
		{
			return output << CharType('(')
				<< value.r << CharType(',') << CharType(' ')
				<< value.g << CharType(',') << CharType(' ')
				<< value.b << CharType(',') << CharType(' ')
				<< value.a << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Color& value)
		{
			CharType unused;
			return input >> unused
				>> value.r >> unused
				>> value.g >> unused
				>> value.b >> unused
				>> value.a >> unused;
		}

		static void _Formatter(FormatData& formatData, const Color& value);

		friend void Formatter(FormatData& formatData, const Color& value)
		{
			_Formatter(formatData, value);
		}
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Color, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Color& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {})", value.r, value.g, value.b, value.a);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.r, value.g, value.b, value.a);
		}
	}
};

namespace std
{
	template <>
	struct hash<s3d::Color>
	{
		[[nodiscard]]
		size_t operator()(const s3d::Color& value) const noexcept
		{
			return s3d::Hash::FNV1a(value);
		}
	};
}
