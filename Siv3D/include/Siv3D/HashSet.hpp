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
# if SIV3D_INTRINSIC(SSE)
#	define PHMAP_HAVE_SSE2 1
#	define PHMAP_HAVE_SSSE3 1
# endif
# include <ThirdParty/parallel_hashmap/phmap.h>

namespace s3d
{
	template <class Type,
		class Hash	= phmap::container_internal::hash_default_hash<Type>,
		class Eq	= phmap::container_internal::hash_default_eq<Type>,
		class Alloc	= phmap::container_internal::Allocator<Type>>
	using HashSet = phmap::flat_hash_set<Type, Hash, Eq, Alloc>;

	template <class Type>
	inline void swap(HashSet<Type>& a, HashSet<Type>& b) noexcept;

	template <class Type>
	inline void Formatter(FormatData& formatData, const HashSet<Type>& set);
}

# include "detail/HashSet.ipp"

# if SIV3D_INTRINSIC(SSE)
#	undef PHMAP_HAVE_SSE2
#	undef PHMAP_HAVE_SSSE3
# endif

