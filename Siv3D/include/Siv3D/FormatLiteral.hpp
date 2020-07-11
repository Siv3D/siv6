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

# ifdef __clang__
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wsign-compare"
# endif
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4389)
# include <ThirdParty/fmt/format.h>
# include <ThirdParty/fmt/ostream.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
# ifdef __clang__
#	pragma clang diagnostic pop
# endif
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	namespace detail
	{
		struct FormatHelper;

		template <class ParseContext>
		inline auto GetFormatTag(std::u32string& representation, ParseContext& ctx)
		{
			auto it = ctx.begin();
			const auto itEnd = ctx.end();

			while (it != itEnd && (*it != '}'))
			{
				representation.push_back(*it++);
			}

			return it;
		}
	}

	[[nodiscard]]
	inline constexpr detail::FormatHelper Fmt(const char32* s) noexcept;

	[[nodiscard]]
	inline constexpr detail::FormatHelper Fmt(StringView s) noexcept;

	[[nodiscard]]
	inline detail::FormatHelper Fmt(const String& s) noexcept;

	[[nodiscard]]
	inline detail::FormatHelper Fmt(const std::u32string& s) noexcept;

	inline namespace Literals
	{
		inline namespace FormatLiterals
		{
			[[nodiscard]]
			inline constexpr detail::FormatHelper operator ""_fmt(const char32* s, size_t length) noexcept;
		}
	}
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::String, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::String& value, FormatContext& ctx)
	{
		const basic_string_view<s3d::char32> sv(value.data(), value.size());

		if (tag.empty())
		{
			return format_to(ctx.out(), sv);
		}
		else
		{
			const std::u32string format = (U"{:" + tag + U'}');
			return format_to(ctx.out(), format, sv);
		}
	}
};

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::StringView, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::StringView& value, FormatContext& ctx)
	{
		const basic_string_view<s3d::char32> sv(value.data(), value.size());

		if (tag.empty())
		{
			return format_to(ctx.out(), sv);
		}
		else
		{
			const std::u32string format = (U"{:" + tag + U'}');
			return format_to(ctx.out(), format, sv);
		}
	}
};

template <class Type, class Allocator>
struct SIV3D_HIDDEN fmt::formatter<s3d::Array<Type, Allocator>, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Array<Type, Allocator>& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			const s3d::String s = s3d::Format(value).replace(U"{", U"{{").replace(U"}", U"}}");
			const basic_string_view<s3d::char32> sv(s.data(), s.size());
			return format_to(ctx.out(), sv);
		}
		else
		{
			const s3d::String format = U"{:" + tag + U'}';
			const auto formatHelper = s3d::Fmt(format);
			const s3d::String s = s3d::Format(value.map([&formatHelper](const auto& e) { return formatHelper(e); })).replace(U"{", U"{{").replace(U"}", U"}}");
			const basic_string_view<s3d::char32> sv(s.data(), s.size());
			return format_to(ctx.out(), sv);
		}
	}
};

# include "detail/FormatLiteral.ipp"
