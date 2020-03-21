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
# include <memory>
# include "Common.hpp"
# include "FormatData.hpp"

namespace s3d
{
	namespace detail
	{
		struct LoggerBuffer
		{
			std::unique_ptr<FormatData> formatData;

			LoggerBuffer();

			LoggerBuffer(LoggerBuffer&& other) noexcept;

			~LoggerBuffer();

			template <class Type>
			LoggerBuffer& operator <<(const Type& value)
			{
				Formatter(*formatData, value);

				return *this;
			}
		};

		struct Logger_impl
		{
			void writeln(const char32_t* s) const;

			void writeln(StringView s) const;

			void writeln(const String& s) const;

			template <class... Args>
			void writeln(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

			void operator()(const char32_t* s) const;

			void operator()(StringView s) const;

			void operator()(const String& s) const;

			template <class... Args>
			void operator()(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

			template <class Type, class = decltype(Formatter(std::declval<FormatData&>(), std::declval<Type>()))>
			LoggerBuffer operator <<(const Type& value) const
			{
				LoggerBuffer buf;

				Formatter(*buf.formatData, value);

				return buf;
			}
		};
	}

	inline constexpr auto Logger = detail::Logger_impl();
}
