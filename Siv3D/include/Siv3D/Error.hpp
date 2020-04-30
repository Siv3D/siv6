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
# include "String.hpp"
# include "FormatData.hpp"

namespace s3d
{
	class Error
	{
	protected:

		String m_what;

	public:

		Error() = default;

		explicit Error(StringView what)
			: m_what(what) {}

		virtual ~Error() = default;

		[[nodiscard]]
		const String& what() const noexcept
		{
			return m_what;
		}

		[[nodiscard]]
		virtual StringView type() const noexcept
		{
			return StringView(U"Error");
		}

		friend std::ostream& operator <<(std::ostream& output, const Error& value)
		{
			return (output << '[' << value.type() << "] " << value.what().narrow());
		}

		friend std::wostream& operator <<(std::wostream& output, const Error& value)
		{
			return (output << L'[' << value.type() << L"] " << value.what().toWstr());
		}
	};

	class ParseError final : public Error
	{
	public:

		using Error::Error;

		[[nodiscard]]
		StringView type() const noexcept override
		{
			return StringView(U"ParseError");
		}
	};

	class BadOptionalAccess final : public Error
	{
	public:

		using Error::Error;

		[[nodiscard]]
		StringView type() const noexcept override
		{
			return StringView(U"Bad optional access");
		}
	};

	class EngineError final : public Error
	{
	public:

		using Error::Error;

		[[nodiscard]]
		StringView type() const noexcept override
		{
			return StringView(U"EngineError");
		}
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Error& value);
}
