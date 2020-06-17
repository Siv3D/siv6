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

		Image(size_t size, Arg::generator_<std::function<Color(void)>> generator);

		Image(size_t size, Arg::generator_<std::function<Color(Point)>> generator);

		Image(size_t size, Arg::generator_<std::function<Color(Vec2)>> generator);

		Image(size_t size, Arg::generator0_1_<std::function<Color(Vec2)>> generator);


		explicit Image(Size size);

		Image(Size size, Color color);

		Image(Size size, Arg::generator_<std::function<Color(void)>> generator);

		Image(Size size, Arg::generator_<std::function<Color(Point)>> generator);

		Image(Size size, Arg::generator_<std::function<Color(Vec2)>> generator);

		Image(Size size, Arg::generator0_1_<std::function<Color(Vec2)>> generator);


		Image(size_t width, size_t height);

		Image(size_t width, size_t height, Color color);

		Image(size_t width, size_t height, Arg::generator_<std::function<Color(void)>> generator);

		Image(size_t width, size_t height, Arg::generator_<std::function<Color(Point)>> generator);

		Image(size_t width, size_t height, Arg::generator_<std::function<Color(Vec2)>> generator);

		Image(size_t width, size_t height, Arg::generator0_1_<std::function<Color(Vec2)>> generator);


		explicit Image(FilePathView path);

		explicit Image(IReader&& reader, ImageFormat format = ImageFormat::Unspecified);

		Image(FilePathView rgb, FilePathView alpha);

		Image(Color rgb, FilePathView alpha);

		//explicit Image(const Emoji& emoji);

		//explicit Image(const Icon& icon);

		//explicit Image(const Grid<Color>& grid);

		//explicit Image(const Grid<ColorF>& grid);

		template <class Type, class Fty, std::enable_if_t<std::is_invocable_r_v<Color, Fty, Type>>* = nullptr>
		explicit Image(const Grid<Type>& grid, Fty converter);












		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Color, Fty>>* = nullptr>
		static Image Generate(Size size, Fty generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Color, Fty>>* = nullptr>
		static Image Generate(size_t width, size_t height, Fty generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Color, Fty, Point>>* = nullptr>
		static Image Generate(Size size, Fty generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Color, Fty, Point>>* = nullptr>
		static Image Generate(size_t width, size_t height, Fty generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Color, Fty, Vec2>>* = nullptr>
		static Image Generate0_1(Size size, Fty generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Color, Fty, Vec2>>* = nullptr>
		static Image Generate0_1(size_t width, size_t height, Fty generator);
	};
}

# include "detail/Image.ipp"
