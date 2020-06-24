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

		SIV3D_NODISCARD_CXX20
		Vector4D() = default;

		SIV3D_NODISCARD_CXX20
		Vector4D(const Vector4D&) = default;

		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(value_type _x, value_type _y, value_type _z, value_type _w) noexcept;

		template <class X, class Y, class Z, class W>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(X _x, Y _y, Z _z, W _w) noexcept;

		template <class U>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(const Vector4D<U>& v) noexcept;

		template <class X, class Y>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(X _x, Y _y, const Vector2D<value_type>& zw) noexcept;

		template <class X, class W>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(X _x, const Vector2D<value_type>& yz, W _w) noexcept;

		template <class Z, class W>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(const Vector2D<value_type>& xy, Z _z, W _w) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(const Vector2D<value_type>& xy, const Vector2D<value_type>& zw) noexcept;

		template <class X>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(X _x, const Vector3D<value_type>& yzw) noexcept;

		template <class Z>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(const Vector3D<value_type>& xyz, Z _z) noexcept;

		[[nodiscard]]
		constexpr value_type elem(size_t index) const noexcept;

		[[nodiscard]]
		value_type* getPointer() noexcept;

		[[nodiscard]]
		const value_type* getPointer() const noexcept;

		//[[nodiscard]]
		//constexpr Vector4D operator +() const noexcept;

		//[[nodiscard]]
		//constexpr Vector4D operator -() const noexcept;

		//[[nodiscard]]
		//constexpr Vector4D operator +(Vector4D v) const noexcept;

		//[[nodiscard]]
		//constexpr Vector4D operator -(Vector4D v) const noexcept;

		//[[nodiscard]]
		//constexpr Vector4D operator *(value_type s) const noexcept;

		//[[nodiscard]]
		//constexpr Vector4D operator *(Vector4D v) const noexcept;

		//[[nodiscard]]
		//constexpr Vector4D operator /(value_type s) const noexcept;

		//[[nodiscard]]
		//constexpr Vector4D operator /(Vector4D v) const noexcept;

		//constexpr Vector4D& operator +=(Vector4D v) noexcept;

		//constexpr Vector4D& operator -=(Vector4D v) noexcept;

		//constexpr Vector4D& operator *=(value_type s) noexcept;

		//constexpr Vector4D& operator *=(Vector4D v) noexcept;

		//constexpr Vector4D& operator /=(value_type s) noexcept;

		//constexpr Vector4D& operator /=(Vector4D v) noexcept;

		template <class U, std::enable_if_t<std::is_scalar_v<U>>* = nullptr>
		[[nodiscard]]
		friend constexpr Vector4D operator *(U s, const Vector4D& v) noexcept
		{
			return (v * static_cast<Type>(s));
		}

		[[nodiscard]]
		friend constexpr bool operator ==(const Vector4D& lhs, const Vector4D& rhs) noexcept
		{
			return (lhs.x == rhs.x)
				&& (lhs.y == rhs.y)
				&& (lhs.z == rhs.z)
				&& (lhs.w == rhs.w);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Vector4D& lhs, const Vector4D& rhs) noexcept
		{
			return (lhs.x != rhs.x)
				|| (lhs.y != rhs.y)
				|| (lhs.z != rhs.z)
				|| (lhs.w != rhs.w);
		}





		[[nodiscard]]
		size_t hash() const noexcept
		{
			return Hash::FNV1a(*this);
		}

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

template <class Type>
struct std::hash<s3d::Vector4D<Type>>
{
	[[nodiscard]]
	size_t operator()(const s3d::Vector4D<Type>& value) const noexcept
	{
		return value.hash();
	}
};
