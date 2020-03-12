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
# include "String.hpp"
# include <ThirdParty/fmt/format.h>
# include <ThirdParty/fmt/ostream.h>

namespace s3d
{
	namespace detail
	{
		struct FormatHelper : fmt::basic_string_view<char32>
		{
			using fmt::basic_string_view<char32>::basic_string_view;

			template <class... Args>
			[[nodiscard]]
			String operator()(Args&& ...args) const
			{
				return fmt::format(*this, std::forward<Args>(args)...);
			}
		};
	}

	[[nodiscard]]
	inline detail::FormatHelper Fmt(const String& s) noexcept
	{
		return detail::FormatHelper{ s.c_str(), s.size() };
	}

	[[nodiscard]]
	constexpr detail::FormatHelper Fmt(StringView s) noexcept
	{
		return detail::FormatHelper{ s.data(), s.size() };
	}

	[[nodiscard]]
	constexpr detail::FormatHelper Fmt(const char32* s) noexcept
	{
		return detail::FormatHelper{ s, std::char_traits<char32>::length(s) };
	}

	inline namespace Literals
	{
		inline namespace FormatLiterals
		{
			[[nodiscard]]
			constexpr detail::FormatHelper operator ""_fmt(const char32* s, size_t length) noexcept
			{
				return detail::FormatHelper{ s, length };
			}
		}
	}
}
