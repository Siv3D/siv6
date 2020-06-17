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
# include "Array.hpp"
# include "NamedParameter.hpp"
# include "PredefinedNamedParameter.hpp"
# include "ImageFormat.hpp"

namespace s3d
{
	class Image
	{
	private:

		using base_type = Array<Color>;

		base_type m_data;

		uint32 m_width = 0;

		uint32 m_height = 0;

	public:

		/// @brief 作成可能な最大の画像の幅
		static constexpr int32 MaxWidth		= 16384;

		/// @brief 作成可能な最大の画像の高さ
		static constexpr int32 MaxHeight	= 16384;

		using iterator					= base_type::iterator;
		using const_iterator			= base_type::const_iterator;
		using reverse_iterator			= base_type::reverse_iterator;
		using const_reverse_iterator	= base_type::const_reverse_iterator;

		Image() = default;

		Image(const Image&) = default;

		Image(Image&& image) noexcept;


		explicit Image(size_t size);

		explicit Image(size_t size, Color color);

		template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty>
			|| std::is_invocable_r_v<Color, Fty, Point> || std::is_invocable_r_v<Color, Fty, int32, int32>)>* = nullptr>
		Image(size_t size, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty, Vec2> || std::is_invocable_r_v<Color, Fty, double, double>)>* = nullptr>
		Image(size_t size, Arg::generator0_1_<Fty> generator);



		Image(size_t width, size_t height);

		Image(size_t width, size_t height, Color color);

		template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty>
			|| std::is_invocable_r_v<Color, Fty, Point> || std::is_invocable_r_v<Color, Fty, int32, int32>)>* = nullptr>
		Image(size_t width, size_t height, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty, Vec2> || std::is_invocable_r_v<Color, Fty, double, double>)>* = nullptr>
		Image(size_t width, size_t height, Arg::generator0_1_<Fty> generator);



		explicit Image(Size size);

		Image(Size size, Color color);

		template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty>
			|| std::is_invocable_r_v<Color, Fty, Point> || std::is_invocable_r_v<Color, Fty, int32, int32>)>* = nullptr>
		Image(Size size, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty, Vec2> || std::is_invocable_r_v<Color, Fty, double, double>)>* = nullptr>
		Image(Size size, Arg::generator0_1_<Fty> generator);





		explicit Image(FilePathView path);

		explicit Image(IReader&& reader, ImageFormat format = ImageFormat::Unspecified);

		Image(FilePathView rgb, FilePathView alpha);

		Image(Color rgb, FilePathView alpha);

		//explicit Image(const Emoji& emoji);

		//explicit Image(const Icon& icon);

		//explicit Image(const Grid<Color>& grid);

		//explicit Image(const Grid<ColorF>& grid);

		//template <class Type, class Fty, std::enable_if_t<std::is_invocable_r_v<Color, Fty, Type>>* = nullptr>
		//explicit Image(const Grid<Type>& grid, Fty converter);

		Image& operator =(const Image&) = default;

		Image& operator =(Image && image) noexcept;

		/// <summary>
		/// 画像の幅（ピクセル）
		/// </summary>
		[[nodiscard]] int32 width() const noexcept
		{
			return m_width;
		}

		/// <summary>
		/// 画像の高さ（ピクセル）
		/// </summary>
		[[nodiscard]] int32 height() const noexcept
		{
			return m_height;
		}

		/// <summary>
		/// 画像の幅と高さ（ピクセル）
		/// </summary>
		[[nodiscard]] Size size() const noexcept
		{
			return{ m_width, m_height };
		}

		/// <summary>
		/// 画像の各行のデータサイズ
		/// </summary>
		[[nodiscard]] uint32 stride() const noexcept
		{
			return m_width * sizeof(Color);
		}

		/// <summary>
		/// 画像のピクセル数
		/// </summary>
		[[nodiscard]] uint32 num_pixels() const noexcept
		{
			return m_width * m_height;
		}

		/// <summary>
		/// 画像のデータサイズ
		/// </summary>
		[[nodiscard]] uint32 size_bytes() const
		{
			return stride() * m_height;
		}

		[[nodiscard]]
		bool isEmpty() const
		{
			return m_data.empty();
		}

		[[nodiscard]]
		explicit operator bool() const
		{
			return not m_data.empty();
		}

		/// <summary>
		/// 画像の不要なメモリ消費を削除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void shrink_to_fit()
		{
			m_data.shrink_to_fit();
		}

		/// <summary>
		/// 画像を消去し、空の画像にします。
		/// </summary>
		/// <remarks>
		/// メモリを解放したい場合は shrink_to_fit() を呼びます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void clear()
		{
			m_data.clear();

			m_width = m_height = 0;
		}

		void release();

		/// <summary>
		/// 画像を別の画像と交換します。
		/// </summary>
		/// <param name="image">
		/// 交換する画像
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void swap(Image& image) noexcept;

		/// <summary>
		/// 画像をコピーした新しい画像を返します。
		/// </summary>
		/// <returns>
		/// コピーした新しい画像
		/// </returns>
		[[nodiscard]] Image cloned() const;

		/// <summary>
		/// 指定した行の先頭ポインタを返します。
		/// </summary>
		/// <param name="y">
		/// 位置(行)
		/// </param>
		/// <returns>
		/// image[y][x] で指定したピクセルにアクセスします。
		/// </returns>
		/// <returns>
		/// 指定した行の先頭ポインタ
		/// </returns>
		[[nodiscard]] Color* operator[](size_t y)
		{
			return m_data.data() + (m_width * y);
		}

		[[nodiscard]] Color& operator[](const Point& pos)
		{
			return *(m_data.data() + (static_cast<size_t>(m_width) * pos.y + pos.x));
		}

		/// <summary>
		/// 指定した行の先頭ポインタを返します。
		/// </summary>
		/// <param name="y">
		/// 位置(行)
		/// </param>
		/// <returns>
		/// image[y][x] で指定したピクセルにアクセスします。
		/// </returns>
		/// <returns>
		/// 指定した行の先頭ポインタ
		/// </returns>
		[[nodiscard]] const Color* operator[](size_t y) const
		{
			return m_data.data() + (m_width * y);
		}

		[[nodiscard]] const Color& operator[](const Point& pos) const
		{
			return *(m_data.data() + (static_cast<size_t>(m_width) * pos.y + pos.x));
		}

		/// <summary>
		/// 画像データの先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 画像データの先頭へのポインタ
		/// </returns>
		[[nodiscard]] Color* data()
		{
			return m_data.data();
		}

		/// <summary>
		/// 画像データの先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 画像データの先頭へのポインタ
		/// </returns>
		[[nodiscard]] const Color* data() const
		{
			return m_data.data();
		}

		/// <summary>
		/// 画像データの先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 画像データの先頭へのポインタ
		/// </returns>
		[[nodiscard]] uint8* dataAsUint8()
		{
			return static_cast<uint8*>(static_cast<void*>(m_data.data()));
		}

		/// <summary>
		/// 画像データの先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 画像データの先頭へのポインタ
		/// </returns>
		[[nodiscard]] const uint8* dataAsUint8() const
		{
			return static_cast<const uint8*>(static_cast<const void*>(&m_data[0]));
		}

		[[nodiscard]]
		Array<Color> asArray() const&
		{
			return m_data;
		}

		[[nodiscard]]
		Array<Color> asArray() &&
		{
			return std::move(m_data);
		}

		/// <summary>
		/// 画像の先頭位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭位置のイテレータ
		/// </returns>
		[[nodiscard]] iterator begin() noexcept { return m_data.begin(); }

		/// <summary>
		/// 画像の先頭位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭位置のイテレータ
		/// </returns>
		[[nodiscard]] const_iterator begin() const noexcept { return m_data.begin(); }

		/// <summary>
		/// 画像の先頭位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭位置のイテレータ
		/// </returns>
		[[nodiscard]] const_iterator cbegin() const noexcept { return m_data.cbegin(); }

		/// <summary>
		/// 画像の終了位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の終了位置のイテレータ
		/// </returns>
		[[nodiscard]] iterator end() noexcept { return m_data.end(); }

		/// <summary>
		/// 画像の終了位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の終了位置のイテレータ
		/// </returns>
		[[nodiscard]] const_iterator end() const noexcept { return m_data.end(); }

		/// <summary>
		/// 画像の終了位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の終了位置のイテレータ
		/// </returns>
		[[nodiscard]] const_iterator cend() const noexcept { return m_data.cend(); }

		/// <summary>
		/// 画像の末尾へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の末尾へのリバースイテレータ
		/// </returns>
		[[nodiscard]] reverse_iterator rbegin() noexcept { return m_data.rbegin(); }

		/// <summary>
		/// 画像の末尾へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の末尾へのリバースイテレータ
		/// </returns>
		[[nodiscard]] const_reverse_iterator rbegin() const noexcept { return m_data.rbegin(); }

		/// <summary>
		/// 画像の末尾へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の末尾へのリバースイテレータ
		/// </returns>
		[[nodiscard]] const_reverse_iterator crbegin() const noexcept { return m_data.crbegin(); }

		/// <summary>
		/// 画像の先頭の前へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭の前へのリバースイテレータ
		/// </returns>
		[[nodiscard]] reverse_iterator rend() noexcept { return m_data.rend(); }

		/// <summary>
		/// 画像の先頭の前へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭の前へのリバースイテレータ
		/// </returns>
		[[nodiscard]] const_reverse_iterator rend() const noexcept { return m_data.rend(); }

		/// <summary>
		/// 画像の先頭の前へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭の前へのリバースイテレータ
		/// </returns>
		[[nodiscard]] const_reverse_iterator crend() const noexcept { return m_data.crend(); }


		/// <summary>
		/// 画像を指定した色で塗りつぶします。
		/// </summary>
		/// <param name="color">
		/// 塗りつぶしの色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void fill(const Color& color);







		template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty>
			|| std::is_invocable_r_v<Color, Fty, Point> || std::is_invocable_r_v<Color, Fty, int32, int32>)>* = nullptr>
		static Image Generate(Size size, Fty generator);

		template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty, Vec2> || std::is_invocable_r_v<Color, Fty, double, double>)>* = nullptr>
		static Image Generate0_1(Size size, Fty generator);
	};
}

# include "detail/Image.ipp"
