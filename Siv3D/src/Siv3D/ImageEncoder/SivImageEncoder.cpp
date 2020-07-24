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
	namespace ImageEncoder
	{

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
