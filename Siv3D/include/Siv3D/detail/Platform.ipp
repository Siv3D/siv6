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

namespace s3d::detail
{
# if SIV3D_PLATFORM(WINDOWS)

	template <size_t Alignment>
	[[nodiscard]]
	inline void* AlignedMalloc(size_t size) noexcept
	{
		return ::_aligned_malloc(size, Alignment);
	}

	inline void AlignedFree(void* const p) noexcept
	{
		::_aligned_free(p);
	}

# elif SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX) || SIV3D_PLATFORM(WEB)

	template <size_t Alignment>
	[[nodiscard]]
	inline void* AlignedMalloc(size_t size) noexcept
	{
		if (Alignment > Platform::MinAlignment)
		{
			void* p = nullptr;
			::posix_memalign(&p, Alignment, size);
			return p;
		}
		else
		{
			return std::malloc(size);
		}
	}

	inline void AlignedFree(void* const p) noexcept
	{
		std::free(p);
	}

# else

	# error Unimplemented

# endif
}
