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
# include "IImageEncoder.hpp"
# include <Siv3D/IImageEncoder.hpp>
# include <Siv3D/Array.hpp>

namespace s3d
{
	class CImageEncoder final : public ISiv3DImageEncoder
	{
	private:

		Array<std::unique_ptr<IImageEncoder>> m_encoders;

	public:

		CImageEncoder() = default;

		~CImageEncoder();

		void init() override;

		bool add(std::unique_ptr<IImageEncoder>&& encoder) override;

		void remove(StringView name) override;

		const Array<std::unique_ptr<IImageEncoder>>& enumEncoder() const noexcept override;
	};
}
