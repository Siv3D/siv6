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

namespace s3d
{
	template <class Type>
	inline Type Parse(const StringView s)
	{
		if constexpr (std::is_integral_v<Type>)
		{
			return ParseInt<Type>(s);
		}
		else if constexpr (std::is_floating_point_v<Type>)
		{
			return ParseFloat<Type>(s);
		}
		else
		{
			Type to;

			if (!(std::wistringstream{ Unicode::ToWstring(s) } >> to))
			{
				throw ParseError(U"Parse<{}>(\"{}\") failed"_fmt(Demangle(typeid(Type).name()), s));
			}

			return to;
		}
	}

	template <>
	inline bool Parse<bool>(const StringView s)
	{
		return ParseBool(s);
	}

	template <>
	inline char Parse<char>(const StringView s)
	{
		const String t = String(s).trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return static_cast<char>(t[0]);
	}

	template <>
	inline char32 Parse<char32>(const StringView s)
	{
		const String t = String(s).trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return t[0];
	}

	template <>
	inline String Parse<String>(const StringView s)
	{
		return String(s).trimmed();
	}
}
