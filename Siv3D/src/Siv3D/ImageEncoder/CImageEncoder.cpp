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

# include <Siv3D/FileSystem.hpp>
# include "CImageEncoder.hpp"
# include <Siv3D/EngineLog.hpp>
//# include <Siv3D/ImageFormat/BMPEncoder.hpp>
//# include <Siv3D/ImageFormat/PNGEncoder.hpp>

namespace s3d
{
	CImageEncoder::~CImageEncoder()
	{
		LOG_SCOPED_TRACE(U"CImageEncoder::~CImageEncoder()");
	}

	void CImageEncoder::init()
	{
		LOG_SCOPED_TRACE(U"CImageEncoder::init()");

		//m_Encoders.push_back(std::make_unique<BMPEncoder>());
		//m_Encoders.push_back(std::make_unique<PNGEncoder>());
	}

	bool CImageEncoder::add(std::unique_ptr<IImageEncoder>&& encoder)
	{
		const StringView name = encoder->name();

		const bool exisits = m_encoders.includes_if([name](const std::unique_ptr<IImageEncoder>& encoder)
			{
				return encoder->name() == name;
			});

		if (exisits)
		{
			return false;
		}

		m_encoders.push_back(std::move(encoder));

		return true;
	}

	void CImageEncoder::remove(const StringView name)
	{
		m_encoders.remove_if([name](const std::unique_ptr<IImageEncoder>& encoder)
			{
				return encoder->name() == name;
			});
	}

	const Array<std::unique_ptr<IImageEncoder>>& CImageEncoder::enumEncoder() const noexcept
	{
		return m_encoders;
	}
}
