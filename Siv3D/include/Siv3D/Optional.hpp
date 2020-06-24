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
# include <cassert>
# include <memory>
# include "Common.hpp"
# include "Utility.hpp"
# include "Error.hpp"
# include "None.hpp"
# include "FormatData.hpp"
# include "detail/Optional_misc.ipp"

namespace s3d
{
	/// @brief Optional
	/// @tparam Type Optional が持つ値の型
	template <class Type>
	class Optional : private OptionalBase<Type>
	{
	private:

		static_assert(!std::is_same_v<std::decay_t<Type>, None_t>, "bad Type");
		static_assert(!std::is_same_v<std::decay_t<Type>, InPlace_t>, "bad Type");

		Type* dataptr();
		
		constexpr const Type* dataptr() const;
		constexpr const Type& contained_val() const&;
		
		Type& contained_val()&;	
		Type&& contained_val()&&;

		void clear() noexcept;

		template <class... Args>
		void initialize(Args&&... args) noexcept(noexcept(Type(std::forward<Args>(args)...)));

		template <class U, class... Args>
		void initialize(std::initializer_list<U> il, Args&&... args) noexcept(noexcept(Type(il, std::forward<Args>(args)...)));

	public:

		/// @brief Optional が持つ値の型
		using value_type = Type;

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		constexpr Optional() noexcept;

		/// @brief none で初期化するコンストラクタ
		SIV3D_NODISCARD_CXX20
		constexpr Optional(None_t) noexcept;

		/// @brief コピーコンストラクタ
		/// @param rhs 他の Optional オブジェクト
		SIV3D_NODISCARD_CXX20
		Optional(const Optional& rhs);

		/// @brief ムーブコンストラクタ
		/// @param rhs 他の Optional オブジェクト
		SIV3D_NODISCARD_CXX20
		Optional(Optional&& rhs) noexcept(std::is_nothrow_move_constructible_v<Type>);

		/// @brief Optional 値を初期化します。
		/// @param v 初期値
		SIV3D_NODISCARD_CXX20
		constexpr Optional(const value_type& v);

		/// @brief Optional 値を初期化します。
		/// @param v 初期値
		SIV3D_NODISCARD_CXX20
		constexpr Optional(value_type&& v);

		/// @brief 値のコンストラクタ引数を使って Optional 値を作成します。
		/// @tparam ...Args コンストラクタ引数の型
		/// @param ...args コンストラクタ引数
		template <class... Args>
		SIV3D_NODISCARD_CXX20
		explicit constexpr Optional(InPlace_t, Args&&... args);

		/// @brief 値のコンストラクタ引数を使って Optional 値を作成します。
		/// @tparam U コンストラクタ引数の型
		/// @tparam ...Args コンストラクタ引数の型
		/// @param il コンストラクタ引数
		/// @param ...args コンストラクタ引数
		template <class U, class... Args, std::enable_if_t<std::is_constructible_v<Type, std::initializer_list<U>>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		explicit constexpr Optional(InPlace_t, std::initializer_list<U> il, Args&&... args);

		/// @brief none を代入して無効値にします。
		/// @param none
		/// @return *this
		Optional& operator =(None_t) noexcept;

		/// @brief Optional 値をコピー代入します。
		/// @param rhs Optional 値
		/// @return *this
		Optional& operator =(const Optional& rhs);

		/// @brief Optional 値をムーブ代入します。
		/// @param rhs Optional 値
		/// @return *this
		Optional& operator =(Optional&& rhs) noexcept(std::is_nothrow_move_assignable_v<Type>&& std::is_nothrow_move_constructible_v<Type>);

		/// @brief 値をムーブ代入します。
		/// @tparam U 値の型
		/// @param v 値
		/// @return *this
		template <class U, std::enable_if_t<std::is_same_v<std::decay_t<U>, Type>>* = nullptr>
		Optional& operator = (U&& v);

		/// <summary>
		/// Optional オブジェクトを初期化します。
		/// </summary>
		/// <param name="args">
		/// 値のコンストラクタ引数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class... Args>
		void emplace(Args&&... args);

		/// <summary>
		/// Optional オブジェクトを初期化します。
		/// </summary>
		/// <param name="il">
		/// 値のコンストラクタ引数
		/// </param>
		/// <param name="args">
		/// 値のコンストラクタ引数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class U, class... Args>
		void emplace(std::initializer_list<U> il, Args&&... args);

		/// <summary>
		/// 別の Optional オブジェクトと中身を入れ替えます。
		/// </summary>
		/// <param name="another">
		/// 別の Optional オブジェクト
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void swap(Optional<Type>& rhs) noexcept(std::is_nothrow_move_constructible_v<Type> && noexcept(detail::swap_ns::adl_swap(std::declval<Type&>(), std::declval<Type&>())));

		/// <summary>
		/// 中身があるかを返します。
		/// </summary>
		/// <returns>
		/// 中身が none ではない場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]]
		constexpr explicit operator bool() const noexcept;

		/// <summary>
		/// 中身があるかを返します。
		/// </summary>
		/// <returns>
		/// 中身が none ではない場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]]
		constexpr bool has_value() const noexcept;

		/// <summary>
		/// 中身へのポインタを返します。
		/// </summary>
		/// <remarks>
		/// 中身が none の場合の動作は未定義です。
		/// </remarks>
		/// <returns>
		/// 中身へのポインタ
		/// </returns>
		[[nodiscard]]
		constexpr const value_type* operator ->() const;

		/// <summary>
		/// 中身へのポインタを返します。
		/// </summary>
		/// <remarks>
		/// 中身が none の場合の動作は未定義です。
		/// </remarks>
		/// <returns>
		/// 中身へのポインタ
		/// </returns>
		[[nodiscard]]
		value_type* operator ->();

		/// <summary>
		/// 中身の参照を返します。
		/// </summary>
		/// <remarks>
		/// 中身が none の場合の動作は未定義です。
		/// </remarks>
		/// <returns>
		/// 中身の参照
		/// </returns>
		[[nodiscard]]
		constexpr value_type const& operator *() const;

		/// <summary>
		/// 中身の参照を返します。
		/// </summary>
		/// <remarks>
		/// 中身が none の場合の動作は未定義です。
		/// </remarks>
		/// <returns>
		/// 中身の参照
		/// </returns>
		[[nodiscard]]
		value_type& operator *();

		/// <summary>
		/// 中身の参照を返します。
		/// </summary>
		/// <exception cref="BadOptionalAccess">
		/// 中身が none の場合 throw されます。
		/// </exception>
		/// <returns>
		/// 中身の参照
		/// </returns>
		[[nodiscard]]
		constexpr value_type const& value() const;

		/// <summary>
		/// 中身の参照を返します。
		/// </summary>
		/// <exception cref="BadOptionalAccess">
		/// 中身が none の場合 throw されます。
		/// </exception>
		/// <returns>
		/// 中身の参照
		/// </returns>
		[[nodiscard]]
		value_type& value();

		/// <summary>
		/// 中身がある場合はその値を、それ以外の場合は v を返します。
		/// </summary>
		/// <param name="v">
		/// 中身が none の場合に返ってくる値
		/// </param>
		/// <returns>
		/// 中身がある場合はその値、それ以外の場合は v
		/// </returns>
		template <class V>
		[[nodiscard]]
		constexpr value_type value_or(V&& v) const&;

		/// <summary>
		/// 中身がある場合はその値を、それ以外の場合は v を返します。
		/// </summary>
		/// <param name="v">
		/// 中身が none の場合に返ってくる値
		/// </param>
		/// <returns>
		/// 中身がある場合はその値、それ以外の場合は v
		/// </returns>
		template <class V>
		[[nodiscard]]
		value_type value_or(V&& v)&&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<value_type, Fty>>* = nullptr>
		[[nodiscard]]
		constexpr value_type value_or_eval(Fty f) const&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<value_type, Fty>>* = nullptr>
		[[nodiscard]]
		value_type value_or_eval(Fty f)&&;

		/// <summary>
		/// 中身を none にします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void reset() noexcept;

		/// <summary>
		/// 中身に別の値を代入します。
		/// </summary>
		/// <param name="v">
		/// コピーする値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void reset(const value_type& v);

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, value_type&>>* = nullptr>
		void then(Fty f);

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, value_type>>* = nullptr>
		void then(Fty f) const;

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// 中身がある場合は関数 f の戻り値の Optional, それ以外の場合は none
		/// </returns>
		template <class Fty, class R = std::decay_t<std::invoke_result_t<Fty, value_type&>>>
		Optional<R> map(Fty f);

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// 中身がある場合は関数 f の戻り値の Optional, それ以外の場合は none
		/// </returns>
		template <class Fty, class R = std::decay_t<std::invoke_result_t<Fty, value_type>>>
		Optional<R> map(Fty f) const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Optional<Type>& value)
		{
			if (value)
			{
				const CharType opt[] = { '(', 'O','p','t','i','o','n','a','l',')','\0' };
				return output << opt << value.value();
			}
			else
			{
				const CharType no[] = { 'n','o','n','e','\0' };
				return output << no;
			}
		}

		friend void Formatter(FormatData& formatData, const Optional& value)
		{
			if (value)
			{
				formatData.string.append(U"(Optional)"_sv);

				Formatter(formatData, value.value());
			}
			else
			{
				Formatter(formatData, none);
			}
		}
	};

	/// <summary>
	/// Optional
	/// </summary>
	template <class Type>
	class Optional<Type&>
	{
		static_assert(!std::is_same_v<Type, None_t>, "bad Type");
		static_assert(!std::is_same_v<Type, InPlace_t>, "bad Type");
			
		Type* ref;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		SIV3D_NODISCARD_CXX20
		constexpr Optional() noexcept;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param>
		/// 無効値
		/// </param>
		SIV3D_NODISCARD_CXX20
		constexpr Optional(None_t) noexcept;

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		SIV3D_NODISCARD_CXX20
		constexpr Optional(Type& v) noexcept;

		Optional(Type&&) = delete;

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		SIV3D_NODISCARD_CXX20
		constexpr Optional(const Optional& rhs) noexcept;

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		SIV3D_NODISCARD_CXX20
		explicit constexpr Optional(InPlace_t, Type& v) noexcept;

		explicit Optional(InPlace_t, Type&&) = delete;

		/// <summary>
		/// 代入演算子
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Optional& operator =(None_t) noexcept;

		/// <summary>
		/// 代入演算子
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class U, std::enable_if_t<std::is_same_v<std::decay_t<U>, Optional<Type&>>>* = nullptr>
		Optional& operator =(U&& rhs) noexcept;

		/// <summary>
		/// ムーブ代入演算子
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class U, std::enable_if_t<not std::is_same_v<std::decay_t<U>, Optional<Type&>>>* = nullptr>
		Optional& operator =(U&& rhs) noexcept = delete;

		/// <summary>
		/// Optional オブジェクトを初期化します。
		/// </summary>
		/// <param name="v">
		/// 新しい値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void emplace(Type& v) noexcept;

		void emplace(Type&&) = delete;

		/// <summary>
		/// 別の Optional オブジェクトと中身を入れ替えます。
		/// </summary>
		/// <param name="another">
		/// 別の Optional オブジェクト
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void swap(Optional<Type&>& rhs) noexcept;

		/// <summary>
		/// 中身があるかを返します。
		/// </summary>
		/// <returns>
		/// 中身が none ではない場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]]
		explicit constexpr operator bool() const noexcept;

		/// <summary>
		/// 中身があるかを返します。
		/// </summary>
		/// <returns>
		/// 中身が none ではない場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]]
		constexpr bool has_value() const noexcept;

		/// <summary>
		/// 中身へのポインタを返します。
		/// </summary>
		/// <remarks>
		/// 中身が none の場合の動作は未定義です。
		/// </remarks>
		/// <returns>
		/// 中身へのポインタ
		/// </returns>
		[[nodiscard]]
		constexpr Type* operator ->() const;

		/// <summary>
		/// 中身の参照を返します。
		/// </summary>
		/// <remarks>
		/// 中身が none の場合の動作は未定義です。
		/// </remarks>
		/// <returns>
		/// 中身の参照
		/// </returns>
		[[nodiscard]]
		constexpr Type& operator *() const;

		/// <summary>
		/// 中身の参照を返します。
		/// </summary>
		/// <exception cref="BadOptionalAccess">
		/// 中身が none の場合 throw されます。
		/// </exception>
		/// <returns>
		/// 中身の参照
		/// </returns>
		[[nodiscard]]
		constexpr Type& value() const;

		/// <summary>
		/// 中身がある場合はその値を、それ以外の場合は v を返します。
		/// </summary>
		/// <param name="v">
		/// 中身が none の場合に返ってくる値
		/// </param>
		/// <returns>
		/// 中身がある場合はその値、それ以外の場合は v
		/// </returns>
		template <class V>
		[[nodiscard]]
		constexpr std::decay_t<Type> value_or(V&& v) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<std::decay_t<Type>, Fty>>* = nullptr>
		[[nodiscard]]
		constexpr std::decay_t<Type> value_or_eval(Fty f) const;

		/// <summary>
		/// 中身を none にします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void reset() noexcept;

		/// <summary>
		/// 中身に別の値を代入します。
		/// </summary>
		/// <param name="v">
		/// コピーする値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void reset(Type& v) noexcept;

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>* = nullptr>
		void then(Fty f);

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, const Type&>>* = nullptr>
		void then(Fty f) const;

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// 中身がある場合は関数 f の戻り値の Optional, それ以外の場合は none
		/// </returns>
		template <class Fty, class R = std::invoke_result_t<Fty, Type&>>
		Optional<R> map(Fty f);

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// 中身がある場合は関数 f の戻り値の Optional, それ以外の場合は none
		/// </returns>
		template <class Fty, class R = std::invoke_result_t<Fty, const Type&>>
		Optional<R> map(Fty f) const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Optional<Type&>& value)
		{
			if (value)
			{
				const CharType opt[] = { '(', 'O','p','t','i','o','n','a','l',')','\0' };
				return output << opt << value.value();
			}
			else
			{
				const CharType no[] = { 'n','o','n','e','\0' };
				return output << no;
			}
		}

		friend void Formatter(FormatData& formatData, const Optional& value)
		{
			if (value)
			{
				formatData.string.append(U"(Optional)"_sv);

				Formatter(formatData, value.value());
			}
			else
			{
				Formatter(formatData, none);
			}
		}
	};

	template <class Type>
	class Optional<Type&&>
	{
		static_assert(sizeof(Type) == 0, "Optional rvalue referencs disallowed");
	};

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator ==(const Optional<Type>& x, const Optional<Type>& y);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator !=(const Optional<Type>& x, const Optional<Type>& y);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <(const Optional<Type>& x, const Optional<Type>& y);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >(const Optional<Type>& x, const Optional<Type>& y);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <=(const Optional<Type>& x, const Optional<Type>& y);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >=(const Optional<Type>& x, const Optional<Type>& y);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator ==(const Optional<Type>& x, None_t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator ==(None_t, const Optional<Type>& x) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator !=(const Optional<Type>& x, None_t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator !=(None_t, const Optional<Type>& x) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <(const Optional<Type>&, None_t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <(None_t, const Optional<Type>& x) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <=(const Optional<Type>& x, None_t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <=(None_t, const Optional<Type>&) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >(const Optional<Type>& x, None_t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >(None_t, const Optional<Type>&) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >=(const Optional<Type>&, None_t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >=(None_t, const Optional<Type>& x) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator ==(const Optional<Type>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator ==(const Type& v, const Optional<Type>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator !=(const Optional<Type>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator !=(const Type& v, const Optional<Type>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <(const Optional<Type>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >(const Type& v, const Optional<Type>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >(const Optional<Type>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <(const Type& v, const Optional<Type>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >=(const Optional<Type>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <=(const Type& v, const Optional<Type>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <=(const Optional<Type>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >=(const Type& v, const Optional<Type>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator ==(const Optional<Type&>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator ==(const Type& v, const Optional<Type&>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator !=(const Optional<Type&>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator !=(const Type& v, const Optional<Type&>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <(const Optional<Type&>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >(const Type& v, const Optional<Type&>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >(const Optional<Type&>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <(const Type& v, const Optional<Type&>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >=(const Optional<Type&>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <=(const Type& v, const Optional<Type&>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <=(const Optional<Type&>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >=(const Type& v, const Optional<Type&>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator ==(const Optional<const Type&>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator ==(const Type& v, const Optional<const Type&>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator !=(const Optional<const Type&>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator !=(const Type& v, const Optional<const Type&>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <(const Optional<const Type&>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >(const Type& v, const Optional<const Type&>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >(const Optional<const Type&>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <(const Type& v, const Optional<const Type&>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >=(const Optional<const Type&>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <=(const Type& v, const Optional<const Type&>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <=(const Optional<const Type&>& x, const Type& v);

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >=(const Type& v, const Optional<const Type&>& x);

	template <class Type>
	[[nodiscard]]
	inline constexpr Optional<std::decay_t<Type>> MakeOptional(Type&& v);

	template <class Type, class... Args>
	[[nodiscard]]
	inline constexpr Optional<Type> MakeOptional(Args&&... args);

	template <class U>
	[[nodiscard]]
	inline constexpr Optional<U&> MakeOptional(std::reference_wrapper<U> v);

	template <class Type>
	inline void swap(Optional<Type>& a, Optional<Type>& b) noexcept(noexcept(a.swap(b)));

	template <class Type>
	Optional(Type) -> Optional<Type>;
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <class Type>
struct std::hash<s3d::Optional<Type>>
{
	[[nodiscard]]
	size_t operator()(const s3d::Optional<Type>& value) const noexcept
	{
		if (value)
		{
			return std::hash<Type>{}(*value);
		}
		else
		{
			return 0;
		}
	}
};

template <class Type>
struct std::hash<s3d::Optional<Type&>>
{
	[[nodiscard]]
	size_t operator()(const s3d::Optional<Type>& value) const noexcept
	{
		if (value)
		{
			return std::hash<Type>{}(*value);
		}
		else
		{
			return 0;
		}
	}
};

# include "detail/Optional.ipp"
