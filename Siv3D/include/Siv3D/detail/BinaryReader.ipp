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
	inline BinaryReader::BinaryReader(const FilePathView path, const OpenMode openMode)
		: BinaryReader()
	{
		open(path, openMode);
	}

	inline bool BinaryReader::supportsLookahead() const noexcept
	{
		return true;
	}

	inline BinaryReader::operator bool() const noexcept
	{
		return isOpen();
	}

# if __cpp_lib_concepts
	template <Concept::TriviallyCopyable Type>
# else
	template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>*>
# endif
	inline bool BinaryReader::read(Type& dst)
	{
		return (read(std::addressof(dst), sizeof(Type)) == sizeof(Type));
	}

# if __cpp_lib_concepts
	template <Concept::TriviallyCopyable Type>
# else
	template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>*>
# endif
	bool BinaryReader::lookahead(Type& dst)
	{
		return (lookahead(std::addressof(dst), sizeof(Type)) == sizeof(Type));
	}
}
