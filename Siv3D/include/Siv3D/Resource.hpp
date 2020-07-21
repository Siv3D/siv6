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
# include "String.hpp"
# include "Array.hpp"
# include "ResourceOption.hpp"

namespace s3d
{
	[[nodiscard]]
	const Array<FilePath>& EnumResourceFiles() noexcept;
	
	[[nodiscard]]
	FilePath Resource(FilePathView path);

	void SetResourceOption(ResourceOption resourceOption);

	[[nodiscard]]
	ResourceOption GetResourceOption() noexcept;

	[[nodiscard]]
	inline FilePath FileOrResource(FilePathView path);
}

# include "detail/Resource.ipp"
