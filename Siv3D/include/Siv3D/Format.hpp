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
# include <xmmintrin.h>
# if  __has_include(<compare>)
#	include <compare>
# endif
# include "PlaceHolder.hpp"
# include "FormatData.hpp"

namespace s3d
{
	namespace detail
	{
		/// <summary>
		/// Format_impl の内部で使用するクラス
		/// </summary>
		template <class...>
		struct FormatArgValidation : std::true_type {};

		/// <summary>
		/// Format_impl の内部で使用するクラス
		/// </summary>
		template <class T, class... TT>
		struct FormatArgValidation<T, TT...> : std::bool_constant<!(std::is_same_v<std::decay_t<T>, char*> || std::is_same_v<std::decay_t<T>, wchar_t*>) && FormatArgValidation<TT...>::value> {};

		struct FormatPlaceholder_impl
		{
		private:

			String m_head;

			String m_tail;

		public:

			SIV3D_NODISCARD_CXX20
			FormatPlaceholder_impl(String&& head, String&& tail) noexcept
				: m_head(std::move(head))
				, m_tail(std::move(tail)) {}

			template <class Type>
			[[nodiscard]]
			String operator ()(const Type& value) const;
		};

		struct Format_impl
		{
		private:

			static void Apply(const FormatData&)
			{
				return;
			}

			template <class Type, class... Args>
			static void Apply(FormatData& formatData, const Type& value, const Args&... args)
			{
				Formatter(formatData, value);

				Apply(formatData, args...);
			}

		public:

			/// <summary>
			/// 一連の引数を文字列に変換します。
			/// </summary>
			/// <param name="args">
			/// 変換する値
			/// </param>
			/// <returns>
			/// 引数を文字列に変換して連結した文字列
			/// </returns>
			template <class... Args, std::enable_if_t<FormatArgValidation<Args...>::value>* = nullptr>
			[[nodiscard]]
			String operator ()(const Args&... args) const
			{
				FormatData formatData;

				Apply(formatData, args...);

				return std::move(formatData.string);
			}

			template <class... Args, std::enable_if_t<!FormatArgValidation<Args...>::value>* = nullptr>
			[[nodiscard]]
			String operator ()(const Args&...) const
			{
				// font(...) などで、U"..." (const char32*) ではない文字列が使われていることを知らせるエラーです
				static_assert(FormatArgValidation<Args...>::value, "string literal \"\" and L\"\" cannot be used in Format(). Use U\"\" instead.");

				return String();
			}

			/// <summary>
			/// 引数を文字列に変換します。
			/// </summary>
			/// <param name="ch">
			/// 変換する値
			/// </param>
			/// <returns>
			/// 引数を文字列に変換した文字列
			/// </returns>
			[[nodiscard]]
			String operator ()(const char32 ch) const
			{
				return String(1, ch);
			}

			/// <summary>
			/// 引数を文字列に変換します。
			/// </summary>
			/// <param name="s">
			/// 変換する文字列
			/// </param>
			/// <returns>
			/// 引数を文字列に変換した文字列
			/// </returns>
			[[nodiscard]]
			String operator ()(const char32* s) const
			{
				return String(s);
			}

			[[nodiscard]]
			String operator ()(StringView s) const
			{
				return String(s);
			}

			/// <summary>
			/// 引数を文字列に変換します。
			/// </summary>
			/// <param name="str">
			/// 変換する文字列
			/// </param>
			/// <returns>
			/// 引数を文字列に変換した文字列
			/// </returns>
			[[nodiscard]]
			const String& operator ()(const String& s) const
			{
				return s;
			}

			/// <summary>
			/// 引数を文字列に変換します。
			/// </summary>
			/// <param name="s">
			/// 変換する文字列
			/// </param>
			/// <returns>
			/// 引数を文字列に変換した文字列
			/// </returns>
			[[nodiscard]]
			String operator ()(String&& s) const noexcept
			{
				return std::move(s);
			}

			[[nodiscard]]
			constexpr Format_impl operator ()(PlaceHolder_t) const
			{
				return detail::Format_impl();
			}

			template <class Head>
			[[nodiscard]]
			FormatPlaceholder_impl operator ()(Head&& head, PlaceHolder_t) const
			{
				return FormatPlaceholder_impl(operator()(std::forward<Head>(head)), String());
			}

			template <class Tail>
			[[nodiscard]]
			FormatPlaceholder_impl operator ()(PlaceHolder_t, Tail&& tail) const
			{
				return FormatPlaceholder_impl(String(), operator()(std::forward<Tail>(tail)));
			}

			template <class Head, class Tail>
			[[nodiscard]]
			FormatPlaceholder_impl operator ()(Head&& head, PlaceHolder_t, Tail&& tail) const
			{
				return FormatPlaceholder_impl(operator()(std::forward<Head>(head)), operator()(std::forward<Tail>(tail)));
			}
		};

		template <class Type>
		String FormatPlaceholder_impl::operator ()(const Type& value) const
		{
			return m_head + Format_impl()(value) + m_tail;
		}
	}

	inline constexpr auto Format = detail::Format_impl();

	void Formatter(FormatData& formatData, FormatData::DecimalPlaces decimalPlace);

	void Formatter(FormatData& formatData, bool value);

	void Formatter(FormatData& formatData, int8 value);

	void Formatter(FormatData& formatData, uint8 value);

	void Formatter(FormatData& formatData, int16 value);

	void Formatter(FormatData& formatData, uint16 value);

	void Formatter(FormatData& formatData, int32 value);

	void Formatter(FormatData& formatData, uint32 value);

	void Formatter(FormatData& formatData, long value);

	void Formatter(FormatData& formatData, unsigned long value);

	void Formatter(FormatData& formatData, long long value);

	void Formatter(FormatData& formatData, unsigned long long value);

	void Formatter(FormatData& formatData, float value);

	void Formatter(FormatData& formatData, double value);

	void Formatter(FormatData& formatData, long double value);

	void Formatter(FormatData& formatData, char ch);

	void Formatter(FormatData& formatData, char8_t ch);

	void Formatter(FormatData& formatData, char16_t ch);

	void Formatter(FormatData& formatData, wchar_t ch);

	void Formatter(FormatData& formatData, char32_t ch);

	void Formatter(FormatData& formatData, std::nullptr_t);

	void Formatter(FormatData& formatData, const void* value);

	void Formatter(FormatData& formatData, const char*) = delete;

	void Formatter(FormatData& formatData, const char8_t*) = delete;

	void Formatter(FormatData& formatData, const char16_t*) = delete;

	void Formatter(FormatData& formatData, const wchar_t*) = delete;

	void Formatter(FormatData& formatData, const char32_t*);

	void Formatter(FormatData& formatData, StringView s);

	void Formatter(FormatData& formatData, const std::u32string& s);

	void Formatter(FormatData& formatData, const String& s);

	void Formatter(FormatData& formatData, __m128 value);

# if __cpp_lib_three_way_comparison

	void Formatter(FormatData& formatData, std::strong_ordering value);

	void Formatter(FormatData& formatData, std::weak_ordering value);

	void Formatter(FormatData& formatData, std::partial_ordering value);

# endif

	template <class ForwardIt>
	inline void Formatter(FormatData& formatData, ForwardIt first, ForwardIt last)
	{
		formatData.string.push_back(U'{');

		bool isFirst = true;

		while (first != last)
		{
			if (isFirst)
			{
				isFirst = false;
			}
			else
			{
				formatData.string.append(U", "_sv);
			}

			Formatter(formatData, *first);

			++first;
		}

		formatData.string.push_back(U'}');
	}

	template <class Type, size_t N>
	inline void Formatter(FormatData& formatData, const Type(&values)[N])
	{
		Formatter(formatData, std::begin(values), std::end(values));
	}

	//template <class Type, size_t N>
	//inline void Formatter(FormatData& formatData, const std::array<Type, N>& v)
	//{
	//	Formatter(formatData, v.begin(), v.end());
	//}

	//template <class Type, class Allocator = std::allocator<Type>>
	//inline void Formatter(FormatData& formatData, const std::vector<Type, Allocator>& v)
	//{
	//	Formatter(formatData, v.begin(), v.end());
	//}

	//template <class Type>
	//inline void Formatter(FormatData& formatData, const std::initializer_list<Type>& ilist)
	//{
	//	Formatter(formatData, ilist.begin(), ilist.end());
	//}

	//template <class Fitrst, class Second>
	//inline void Formatter(FormatData& formatData, const std::pair<Fitrst, Second>& pair)
	//{
	//	formatData.string.push_back(U'{');

	//	Formatter(formatData, pair.first);

	//	formatData.string.append(U", "_sv);

	//	Formatter(formatData, pair.second);

	//	formatData.string.push_back(U'}');
	//}
}
