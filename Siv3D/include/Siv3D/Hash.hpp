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
# include "Concepts.hpp"

namespace s3d
{
	namespace Hash
	{
		inline size_t FNV1a(const void* input, size_t size) noexcept;

	# if __cpp_lib_concepts
		template <Concept::TriviallyCopyable Type>
	# else
		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
	# endif
		inline size_t FNV1a(const Type& input) noexcept;

		inline namespace v073
		{
			inline uint64 XXHash3(const void* input, size_t size) noexcept;

		# if __cpp_lib_concepts
			template <Concept::TriviallyCopyable Type>
		# else
			template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		# endif
			inline uint64 XXHash3(const Type& input) noexcept;
		}
	}
}

# include "detail/Hash.ipp"
