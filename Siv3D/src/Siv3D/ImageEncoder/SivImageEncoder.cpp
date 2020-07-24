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

# include <Siv3D/ImageEncoder.hpp>
# include "IImageEncoder.hpp"
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		constexpr StringView ToString(const ImageFormat imageFormat) noexcept
		{
			switch (imageFormat)
			{
			case ImageFormat::DDS:
				return U"DDS"_sv;
			case ImageFormat::PNG:
				return U"PNG"_sv;
			case ImageFormat::JPEG:
				return U"JPEG"_sv;
			case ImageFormat::JPEG2000:
				return U"JPEG2000"_sv;
			case ImageFormat::BMP:
				return U"BMP"_sv;
			case ImageFormat::WebP:
				return U"WebP"_sv;
			case ImageFormat::GIF:
				return U"GIF"_sv;
			case ImageFormat::TIFF:
				return U"TIFF"_sv;
			case ImageFormat::TGA:
				return U"TGA"_sv;
			case ImageFormat::PPM:
				return U"PPM"_sv;
			default:
				return U""_sv;
			}
		}
	}

	namespace ImageEncoder
	{
		bool Save(const Image& image, const ImageFormat format, const FilePathView path)
		{
			return SIV3D_ENGINE(ImageEncoder)->save(image, detail::ToString(format), path);
		}

		bool Encode(const Image& image, const ImageFormat format, IWriter& writer)
		{
			return SIV3D_ENGINE(ImageEncoder)->encode(image, detail::ToString(format), writer);
		}

		Blob Encode(const Image& image, const ImageFormat format)
		{
			return SIV3D_ENGINE(ImageEncoder)->encode(image, detail::ToString(format));
		}

		bool Add(std::unique_ptr<IImageEncoder>&& Encoder)
		{
			return SIV3D_ENGINE(ImageEncoder)->add(std::move(Encoder));
		}

		void Remove(const StringView name)
		{
			return SIV3D_ENGINE(ImageEncoder)->remove(name);
		}

		const Array<std::unique_ptr<IImageEncoder>>& Enum()
		{
			return SIV3D_ENGINE(ImageEncoder)->enumEncoder();
		}
	}
}
