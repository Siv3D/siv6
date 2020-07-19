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
	namespace detail
	{
		template <class Type>
		inline TextWriterBuffer& TextWriterBuffer::operator <<(const Type& value)
		{
			Formatter(*formatData, value);

			return *this;
		}
	}

	inline TextWriter::operator bool() const noexcept
	{
		return isOpen();
	}

	inline void TextWriter::write(const char32 ch)
	{
		write(StringView(&ch, 1));
	}

	inline void TextWriter::write(const char32* s)
	{
		write(StringView(s));
	}

	inline void TextWriter::write(const String& s)
	{
		write(StringView(s));
	}

# if __cpp_lib_concepts
	template <Concept::Formattable... Args>
# else
	template <class... Args>
# endif
	inline void TextWriter::write(const Args& ... args)
	{
		write(Format(args...));
	}

	inline void TextWriter::writeln(const char32 ch)
	{
		writeln(StringView(&ch, 1));
	}

	inline void TextWriter::writeln(const char32* s)
	{
		writeln(StringView(s));
	}

	inline void TextWriter::writeln(const String& s)
	{
		writeln(StringView(s));
	}

# if __cpp_lib_concepts
	template <Concept::Formattable... Args>
# else
	template <class... Args>
# endif
	inline void TextWriter::writeln(const Args& ... args)
	{
		writeln(Format(args...));
	}

# if __cpp_lib_concepts
	template <Concept::Formattable Type>
# else
	template <class Type>
# endif
	inline detail::TextWriterBuffer TextWriter::operator <<(const Type& value)
	{
		detail::TextWriterBuffer buffer(*this);

		Formatter(*(buffer.formatData), value);

		return buffer;
	}
}
