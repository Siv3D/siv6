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
# include "Fwd.hpp"
# include "Format.hpp"

namespace s3d
{
	namespace detail
	{
		struct ConsoleBuffer
		{
			std::unique_ptr<FormatData> formatData;

			ConsoleBuffer();

			ConsoleBuffer(ConsoleBuffer&& other) noexcept;

			~ConsoleBuffer();

			template <class Type>
			ConsoleBuffer& operator <<(const Type& value)
			{
				Formatter(*formatData, value);

				return *this;
			}
		};

		struct Console_impl
		{
			void open() const;

			void write(const char32_t* s) const;

			void write(StringView s) const;

			void write(const String& s) const;

			template <class... Args>
			void write(const Args&... args) const
			{
				return write(Format(args...));
			}

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
			ConsoleBuffer operator <<(const Type& value) const
			{
				ConsoleBuffer buf;

				Formatter(*buf.formatData, value);

				return buf;
			}
		};
	}

	inline constexpr auto Console = detail::Console_impl();
}
