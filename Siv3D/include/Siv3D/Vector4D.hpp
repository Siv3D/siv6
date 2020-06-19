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
# include "FormatData.hpp"
# include "FormatLiteral.hpp"

namespace s3d
{
	template <class Type>
	struct Vector4D
	{
		using value_type = Type;

		static constexpr size_t Dimension = 4;

		value_type x, y, z, w;

		Vector4D() = default;

		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(value_type _x, value_type _y, value_type _z, value_type _w) noexcept
			: x(_x)
			, y(_y) 
			, z(_z)
			, w(_w) {}

		template <class X, class Y, class Z, class W>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(X _x, Y _y, Z _z, W _w) noexcept
			: x(static_cast<value_type>(_x))
			, y(static_cast<value_type>(_y))
			, z(static_cast<value_type>(_z))
			, w(static_cast<value_type>(_w)) {}

		size_t hash() const noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Vector4D& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(',') << CharType(' ')
				<< value.z << CharType(',') << CharType(' ')
				<< value.w << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Vector4D& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused
				>> value.z >> unused
				>> value.w >> unused;
		}

		friend void Formatter(FormatData& formatData, const Vector4D& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Vector4D& value);
	};

	using Float4	= Vector4D<float>;
	using Vec4		= Vector4D<double>;
}

template <class Type>
struct SIV3D_HIDDEN fmt::formatter<s3d::Vector4D<Type>, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Vector4D<Type>& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {})", value.x, value.y, value.z, value.w);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.x, value.y, value.z, value.w);
		}
	}
};

namespace std
{
	template <class Type>
	struct hash<s3d::Vector4D<Type>>
	{
		[[nodiscard]]
		size_t operator()(const s3d::Vector4D<Type>& value) const noexcept
		{
			return value.hash();
		}
	};
}
