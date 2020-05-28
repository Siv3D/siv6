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
# if __cpp_lib_concepts
	template <Concept::TriviallyCopyable Type>
# else
	template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>*>
# endif
	inline bool IReader::read(Type& to)
	{
		return read(std::addressof(to), sizeof(Type)) == sizeof(Type);
	}

# if __cpp_lib_concepts
	template <Concept::TriviallyCopyable Type>
# else
	template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>*>
# endif
	inline bool IReader::lookahead(Type& to) const
	{
		return lookahead(std::addressof(to), sizeof(Type)) == sizeof(Type);
	}
}
