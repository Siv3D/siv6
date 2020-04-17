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
# include <xxHash/xxh3.h>

namespace s3d
{
	namespace Hash
	{
		inline uint64 FNV1a(const void* input, const size_t size) noexcept
		{
			const uint8* data = static_cast<const uint8*>(input);
			constexpr uint64 offset_basis = 14695981039346656037ULL;
			constexpr uint64 fnv_prime = 1099511628211ULL;

			uint64 result = offset_basis;

			for (uint64 next = 0; next < size; ++next)
			{
				result ^= static_cast<uint64>(data[next]);
				result *= fnv_prime;
			}

			return result;
		}

	# if __cpp_lib_concepts
		template <Concept::TriviallyCopyable Type>
	# else
		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>*>
	# endif
		inline uint64 FNV1a(const Type& input) noexcept
		{
			return FNV1a(std::addressof(input), sizeof(Type));
		}

		inline namespace v073
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
}
