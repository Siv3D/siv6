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

# define CATCH_CONFIG_FAST_COMPILE
# define CATCH_CONFIG_ENABLE_BENCHMARKING
# include <ThirdParty/Catch2/catch.hpp>

# include <Siv3D.hpp>
using namespace s3d;
using namespace std::literals;

TEST_CASE("Image")
{
	SECTION("Decoder BMP")
	{
		{
			const FilePathView path = U"test/image/bmp/1x1_24.bmp";
			const auto info = ImageDecoder::GetImageInfo(path);
			REQUIRE(info.has_value());
			REQUIRE(info->imageFormat == ImageFormat::BMP);
			REQUIRE(info->pixelFormat == PixelFormat::R8G8B8);
			REQUIRE(info->size == Size(1, 1));
			REQUIRE(info->isAnimated == false);

			const Image image(path);
			REQUIRE(image.size() == Size(1, 1));
			REQUIRE(image[0][0] == Color(11, 22, 33));
		}

		{
			const FilePathView path = U"test/image/bmp/3x3_24.bmp";
			const auto info = ImageDecoder::GetImageInfo(path);
			REQUIRE(info.has_value());
			REQUIRE(info->imageFormat == ImageFormat::BMP);
			REQUIRE(info->pixelFormat == PixelFormat::R8G8B8);
			REQUIRE(info->size == Size(3, 3));
			REQUIRE(info->isAnimated == false);

			const Image image(path);
			REQUIRE(image.size() == Size(3, 3));
			REQUIRE(image[0][0] == Color(11, 22, 33));
			REQUIRE(image[0][1] == Color(11, 22, 33));
			REQUIRE(image[0][2] == Color(11, 22, 33));
			REQUIRE(image[1][0] == Color(11, 22, 33));
			REQUIRE(image[1][1] == Color(11, 22, 33));
			REQUIRE(image[1][2] == Color(11, 22, 33));
			REQUIRE(image[2][0] == Color(222, 111, 0));
			REQUIRE(image[2][1] == Color(0, 222, 111));
			REQUIRE(image[2][2] == Color(111, 0, 222));
		}

		{
			const FilePathView path = U"test/image/bmp/1x1_256.bmp";
			const auto info = ImageDecoder::GetImageInfo(path);
			REQUIRE(info.has_value());
			REQUIRE(info->imageFormat == ImageFormat::BMP);
			REQUIRE(info->pixelFormat == PixelFormat::R8G8B8);
			REQUIRE(info->size == Size(1, 1));
			REQUIRE(info->isAnimated == false);

			const Image image(path);
			REQUIRE(image.size() == Size(1, 1));
			REQUIRE(image[0][0] == Color(0, 32, 64));
		}

		{
			const FilePathView path = U"test/image/bmp/3x3_256.bmp";
			const auto info = ImageDecoder::GetImageInfo(path);
			REQUIRE(info.has_value());
			REQUIRE(info->imageFormat == ImageFormat::BMP);
			REQUIRE(info->pixelFormat == PixelFormat::R8G8B8);
			REQUIRE(info->size == Size(3, 3));
			REQUIRE(info->isAnimated == false);

			const Image image(path);
			REQUIRE(image.size() == Size(3, 3));
			REQUIRE(image[0][0] == Color(0, 32, 64));
			REQUIRE(image[0][1] == Color(0, 32, 64));
			REQUIRE(image[0][2] == Color(0, 32, 64));
			REQUIRE(image[1][0] == Color(0, 32, 64));
			REQUIRE(image[1][1] == Color(0, 32, 64));
			REQUIRE(image[1][2] == Color(0, 32, 64));
			REQUIRE(image[2][0] == Color(224, 96, 0));
			REQUIRE(image[2][1] == Color(0, 224, 128));
			REQUIRE(image[2][2] == Color(96, 0, 192));
		}
	}
}
