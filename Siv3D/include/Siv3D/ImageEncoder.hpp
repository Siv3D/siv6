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
# include <memory>
# include "Common.hpp"
# include "IImageEncoder.hpp"

namespace s3d
{
	namespace ImageEncoder
	{
		bool Save(const Image& image, ImageFormat format, FilePathView path);

		bool Encode(const Image& image, ImageFormat format, IWriter& writer);

		Blob Encode(const Image& image, ImageFormat format);

		template <class ImageEncoder>
		bool Add();

		bool Add(std::unique_ptr<IImageEncoder>&& encoder);

		void Remove(StringView name);

		const Array<std::unique_ptr<IImageEncoder>>& Enum();
	}
}

# include "detail/ImageEncoder.ipp"
