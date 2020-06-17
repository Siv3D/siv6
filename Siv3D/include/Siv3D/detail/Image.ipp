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
		[[nodiscard]]
		inline constexpr bool IsValidImageSize(const Size size)
		{
			return InRange(size.x, 0, Image::MaxWidth)
				&& InRange(size.y, 0, Image::MaxHeight);
		}
	}

	inline Image::Image(Image&& image) noexcept
		: m_data(std::move(image.m_data))
		, m_width(image.m_width)
		, m_height(image.m_height)
	{
		image.m_width = image.m_height = 0;
	}


	inline Image::Image(const size_t size)
		: Image(size, size) {}

	inline Image::Image(const size_t size, const Color color)
		: Image(size, size, color) {}

	template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty>
		|| std::is_invocable_r_v<Color, Fty, Point> || std::is_invocable_r_v<Color, Fty, int32, int32>)>*>
	inline Image::Image(const size_t size, Arg::generator_<Fty> generator)
		: Image(size, size, generator) {}

	template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty, Vec2> || std::is_invocable_r_v<Color, Fty, double, double>)>*>
	inline Image::Image(const size_t size, Arg::generator0_1_<Fty> generator)
		: Image(size, size, generator) {}


	inline Image::Image(const size_t width, const size_t height)
		: Image(Size(width, height)) {}

	inline Image::Image(const size_t width, const size_t height, const Color color)
		: Image(Size(width, height), color) {}

	template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty>
		|| std::is_invocable_r_v<Color, Fty, Point> || std::is_invocable_r_v<Color, Fty, int32, int32>)>*>
	inline Image::Image(const size_t width, const size_t height, Arg::generator_<Fty> generator)
		: Image(Size(width, height), generator) {}

	template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty, Vec2> || std::is_invocable_r_v<Color, Fty, double, double>)>*>
	inline Image::Image(const size_t width, const size_t height, Arg::generator0_1_<Fty> generator)
		: Image(Size(width, height), generator) {}


	inline Image::Image(const Size size)
		: m_data(detail::IsValidImageSize(size) ? size.area() : 0)
		, m_width(detail::IsValidImageSize(size) ? size.x : 0)
		, m_height(detail::IsValidImageSize(size) ? size.y : 0) {}

	inline Image::Image(const Size size, const Color color)
		: m_data(detail::IsValidImageSize(size) ? size.area() : 0, color)
		, m_width(detail::IsValidImageSize(size) ? size.x : 0)
		, m_height(detail::IsValidImageSize(size) ? size.y : 0) {}

	template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty>
		|| std::is_invocable_r_v<Color, Fty, Point> || std::is_invocable_r_v<Color, Fty, int32, int32>)>*>
	inline Image::Image(const Size size, Arg::generator_<Fty> generator)
	{
		*this = Generate(size, generator.value());
	}

	template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty, Vec2> || std::is_invocable_r_v<Color, Fty, double, double>)>*>
	inline Image::Image(const Size size, Arg::generator0_1_<Fty> generator)
	{
		*this = Generate0_1(size, generator.value());
	}





	inline Image& Image::operator =(Image&& image) noexcept
	{
		m_data		= std::move(image.m_data);
		m_width		= image.m_width;
		m_height	= image.m_height;

		image.m_width = image.m_height = 0;

		return *this;
	}


	template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty>
		|| std::is_invocable_r_v<Color, Fty, Point> || std::is_invocable_r_v<Color, Fty, int32, int32>)>*>
	inline Image Image::Generate(const Size size, Fty generator)
	{
		Image newImage(size);

		if (!newImage)
		{
			return newImage;
		}

		const int32 width = size.x;
		const int32 height = size.y;
		Color* pDst = newImage.data();

		for (int32 y = 0; y < height; ++y)
		{
			for (int32 x = 0; x < width; ++x)
			{
				if constexpr (std::is_invocable_r_v<Color, Fty, Point>)
				{
					(*pDst++) = generator({ x, y });
				}
				else if constexpr (std::is_invocable_r_v<Color, Fty, int32, int32>)
				{
					(*pDst++) = generator(x, y);
				}
				else // std::is_invocable_r_v<Color, Fty>
				{
					(*pDst++) = generator();
				}
			}
		}

		return newImage;
	}

	template <class Fty, std::enable_if_t<(std::is_invocable_r_v<Color, Fty, Vec2> || std::is_invocable_r_v<Color, Fty, double, double>)>*>
	inline Image Image::Generate0_1(const Size size, Fty generator)
	{
		Image newImage(size);

		if (!newImage)
		{
			return newImage;
		}

		const int32 width = size.x;
		const int32 height = size.y;
		const double sx = 1.0 / (width - 1);
		const double sy = 1.0 / (height - 1);
		Color* pDst = newImage.data();

		for (int32 y = 0; y < height; ++y)
		{
			for (int32 x = 0; x < width; ++x)
			{
				if constexpr (std::is_invocable_r_v<Color, Fty, Vec2>)
				{
					(*pDst++) = generator({ sx * x, sy * y });
				}
				else // std::is_invocable_r_v<Color, Fty, double, double>
				{
					(*pDst++) = generator(sx * x, sy * y);
				}
			}
		}

		return newImage;
	}
}
