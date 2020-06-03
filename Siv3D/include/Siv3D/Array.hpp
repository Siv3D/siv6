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
# include <vector>
# include "Common.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	/// @brief 動的配列
	/// @tparam Type 要素の型
	/// @tparam Allocator アロケータ
	template <class Type, class Allocator = std::allocator<Type>>
	class Array : protected std::vector<Type, Allocator>
	{
	private:

		using base_type = std::vector<Type, Allocator>;

	public:

		using typename base_type::value_type;
		using typename base_type::pointer;
		using typename base_type::const_pointer;
		using typename base_type::reference;
		using typename base_type::const_reference;
		using typename base_type::iterator;
		using typename base_type::const_iterator;
		using typename base_type::reverse_iterator;
		using typename base_type::const_reverse_iterator;
		using typename base_type::size_type;
		using typename base_type::difference_type;
		using typename base_type::allocator_type;

		using base_type::vector;
		using base_type::operator=;
		using base_type::assign;
		using base_type::get_allocator;
		using base_type::front;
		using base_type::back;
		using base_type::data;
		using base_type::begin;
		using base_type::cbegin;
		using base_type::end;
		using base_type::cend;
		using base_type::rbegin;
		using base_type::crbegin;
		using base_type::rend;
		using base_type::crend;
		using base_type::empty;
		using base_type::size;
		using base_type::max_size;
		using base_type::reserve;
		using base_type::capacity;
		using base_type::shrink_to_fit;
		using base_type::clear;
		using base_type::insert;
		using base_type::emplace;
		using base_type::erase;
		using base_type::push_back;
		using base_type::emplace_back;
		using base_type::pop_back;
		using base_type::resize;

		/// @brief デフォルトコンストラクタ
		Array() = default;

		/// @brief コピーコンストラクタ
		/// @param other コピーする配列
		Array(const Array& other) = default;

		/// @brief ムーブコンストラクタ
		/// @param other ムーブする配列
		Array(Array&& other) = default;

		/// @brief コピー代入演算子
		/// @param other コピーする配列
		/// @return *this
		Array& operator =(const Array& other) = default;

		/// @brief ムーブ代入演算子
		/// @param other ムーブする配列
		/// @return *this
		Array& operator =(Array&& other) = default;

		/// @brief ジェネレータ関数を使った配列の作成
		/// @tparam Fty ジェネレータ関数の型
		/// @param size 作成する配列の要素数
		/// @param generator ジェネレータ関数
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		Array(size_type size, Arg::generator_<Fty> generator);

		/// @brief インデックス指定ジェネレータ関数を使った配列の作成
		/// @tparam Fty ジェネレータ関数の型
		/// @param size 作成する配列の要素数
		/// @param indexedGenerator インデックス指定ジェネレータ関数
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>* = nullptr>
		Array(size_type size, Arg::indexedGenerator_<Fty> indexedGenerator);

		/// @brief 他の配列と要素を入れ替えます。
		/// @param other 入れ替える配列
		void swap(Array& other) noexcept;

		/// @brief 配列が空であるかを返します。
		/// @return 配列が空である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief 配列が要素を持っているかを返します。
		/// @return 配列が要素を持っている場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief 配列の要素を全て消去し、メモリも解放します。
		void release();

		/// @brief 配列の要素の合計サイズ（バイト）を返します。
		/// @return 配列の要素の合計サイズ（バイト）
		[[nodiscard]]
		size_t size_bytes() const noexcept;

		/// @brief 配列の先頭に要素を追加します。
		/// @param value 追加する値
		void push_front(const value_type& value);

		/// @brief 配列の先頭に要素を追加します。
		/// @param value 追加する値
		void push_front(value_type&& value);

		/// @brief 配列の先頭から要素を削除します。
		void pop_front();

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @return 要素への参照
		[[nodiscard]]
		const value_type& operator[](size_t index) const&;

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @return 要素への参照
		[[nodiscard]]
		value_type& operator[](size_t index) &;

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @return 要素への参照
		[[nodiscard]]
		value_type operator[](size_t index) &&;

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @throw std::out_of_range 範囲外アクセスの場合 throw
		/// @return 要素への参照
		const value_type& at(size_t index) const&;

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @return 要素への参照
		value_type& at(size_t index) &;

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @return 要素への参照
		value_type at(size_t index) &&;

		/// @brief 配列の末尾に要素を追加します。
		/// @param value 追加する値
		/// @return *this
		Array& operator <<(const value_type& value);

		/// @brief 配列の末尾に要素を追加します。
		/// @param value 追加する値
		/// @return *this
		Array& operator <<(value_type&& value);










		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		static Array Generate(size_type size, Fty generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>* = nullptr>
		static Array IndexedGenerate(size_type size, Fty indexedGenerator);
	};
}

# include "detail/Array.ipp"
