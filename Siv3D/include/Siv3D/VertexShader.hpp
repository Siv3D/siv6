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
# include "AssetHandle.hpp"
# include "Array.hpp"
# include "ConstantBufferBinding.hpp"
# include "Byte.hpp"

namespace s3d
{
	class VertexShader : public AssetHandle<VertexShader>
	{
	public:

		VertexShader();

		VertexShader(FilePathView path, const Array<ConstantBufferBinding>& bindings);

		//virtual ~VertexShader();

		[[nodiscard]]
		size_t getBinarySize() const noexcept;

		[[nodiscard]]
		const Byte* getBinaryData() const noexcept;
	};
}
