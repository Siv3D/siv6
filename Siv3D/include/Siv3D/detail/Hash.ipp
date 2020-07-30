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

namespace s3d
{
	namespace Hash
	{
		inline size_t FNV1a(const void* input, const size_t size) noexcept
		{
			const uint8* data = static_cast<const uint8*>(input);
			const uint8* const end = (data + size);

			if constexpr (sizeof(size_t) == 8)
			{
				constexpr size_t offset_basis	= 14695981039346656037ULL;
				constexpr size_t fnv_prime		= 1099511628211ULL;
				size_t result = offset_basis;

				for (; data != end; ++data)
				{
					result ^= static_cast<size_t>(*data);
					result *= fnv_prime;
				}

				return result;
			}
			else
			{
				constexpr size_t offset_basis	= 2166136261u;
				constexpr size_t fnv_prime		= 16777619u;
				size_t result = offset_basis;

				for (; data != end; ++data)
				{
					result ^= static_cast<size_t>(*data);
					result *= fnv_prime;
				}

				return result;
			}
		}

	# if __cpp_lib_concepts
		template <Concept::TriviallyCopyable Type>
	# else
		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>*>
	# endif
		inline size_t FNV1a(const Type& input) noexcept
		{
			return FNV1a(std::addressof(input), sizeof(Type));
		}

	# if __cpp_lib_concepts
		template <Concept::TriviallyCopyable Type>
	# else
		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>*>
	# endif
		inline uint64 XXHash3(const Type& input) noexcept
		{
			return XXHash3(std::addressof(input), sizeof(Type));
		}
	}
}
