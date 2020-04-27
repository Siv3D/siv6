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

# include <Siv3D/String.hpp>
# include <Siv3D/Char.hpp>

namespace s3d
{
	int32 String::case_insensitive_compare(const StringView view) const noexcept
	{
		auto first1 = begin(), last1 = end();
		auto first2 = view.begin(), last2 = view.end();

		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			const int32 c = CaseInsensitiveCompare(*first1, *first2);

			if (c != 0)
			{
				return c;
			}
		}

		if ((first1 == last1) && (first2 != last2))
		{
			return -1;
		}
		else if ((first1 != last1) && (first2 == last2))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	bool String::case_insensitive_equals(const StringView view) const noexcept
	{
		if (length() != view.length())
		{
			return false;
		}

		auto first1 = begin(), last1 = end();
		auto first2 = view.begin(), last2 = view.end();

		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			const int32 c = CaseInsensitiveCompare(*first1, *first2);

			if (c != 0)
			{
				return false;
			}
		}

		return true;
	}

	String& String::capitalize() noexcept
	{
		for (auto& c : m_string)
		{
			if (IsAlpha(c))
			{
				c = ToUpper(c);
				break;
			}
		}

		return *this;
	}

	String String::expandTabs(const size_t tabSize) const
	{
		const size_t tabCount = count(value_type('\t'));
		const size_t new_size = m_string.length() + (tabCount * tabSize);

		String result(new_size, value_type('\0'));

		value_type* dst = &result[0];

		for (const auto c : m_string)
		{
			if (c == value_type('\t'))
			{
				for (size_t i = 0; i < tabSize; ++i)
				{
					*dst++ = value_type(' ');
				}
			}
			else
			{
				*dst++ = c;
			}
		}

		return result;
	}

	String String::layout(const size_t width) const
	{
		String result;

		result.reserve(m_string.length());

		size_t count = 0;

		for (const auto c : m_string)
		{
			if (c == value_type('\n'))
			{
				result.push_back(value_type('\n'));

				count = 0;
			}
			else if (c != value_type('\r'))
			{
				if (width <= count)
				{
					result.push_back(value_type('\n'));

					count = 0;
				}

				result.push_back(c);

				++count;
			}
		}

		return result;
	}

	String& String::lowercase() noexcept
	{
		for (auto& c : m_string)
		{
			c = ToLower(c);
		}

		return *this;
	}

	String& String::lpad(const size_t length, const value_type fillChar)
	{
		if (length <= m_string.length())
		{
			return *this;
		}

		m_string.insert(m_string.begin(), length - m_string.length(), fillChar);

		return *this;
	}

	String String::lpadded(const size_t length, const value_type fillChar) const &
	{
		if (length <= m_string.length())
		{
			return *this;
		}

		String new_string;

		new_string.reserve(length);

		new_string.assign(length - m_string.length(), fillChar);

		new_string.append(m_string);

		return new_string;
	}

	String String::replaced(const StringView oldStr, const StringView newStr) const
	{
		String new_string;

		if (newStr.length() >= oldStr.length())
		{
			new_string.reserve(m_string.length());
		}

		const auto itEnd = m_string.end();
		auto itCurrent = m_string.begin();
		auto itNext = std::search(itCurrent, itEnd, oldStr.begin(), oldStr.end());

		while (itNext != itEnd)
		{
			new_string.append(itCurrent, itNext);
			new_string.append(newStr);
			itCurrent = itNext + oldStr.length();
			itNext = std::search(itCurrent, itEnd, oldStr.begin(), oldStr.end());
		}

		new_string.append(itCurrent, itNext);

		return new_string;
	}

	String& String::rotate(std::ptrdiff_t count)
	{
		if (m_string.empty())
		{
			;
		}
		else if (count > 0) // rotation to the left
		{
			if (static_cast<size_t>(count) > m_string.size())
			{
				count %= m_string.size();
			}

			std::rotate(m_string.begin(), m_string.begin() + count, m_string.end());
		}
		else if (count < 0) // rotation to the right
		{
			count = -count;

			if (static_cast<size_t>(count) > m_string.size())
			{
				count %= m_string.size();
			}

			std::rotate(m_string.rbegin(), m_string.rbegin() + count, m_string.rend());
		}

		return *this;
	}
}
