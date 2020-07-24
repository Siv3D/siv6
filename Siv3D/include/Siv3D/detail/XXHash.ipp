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
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(26819)
# include <ThirdParty/xxHash/xxh3.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	namespace Hash
	{
		inline uint64 XXHash3(const void* input, const size_t size) noexcept
		{
			return XXH3_64bits(input, size);
		}

	# if __cpp_lib_concepts
		template <Concept::TriviallyCopyable Type>
	# else
		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>*>
	# endif
		inline uint64 XXHash3(const Type& input) noexcept
		{
			return XXH3_64bits(std::addressof(input), sizeof(Type));
		}
	}
}
