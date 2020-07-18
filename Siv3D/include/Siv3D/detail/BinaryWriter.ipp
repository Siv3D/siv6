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
	inline BinaryWriter::BinaryWriter(const FilePathView path, const OpenMode openMode)
		: BinaryWriter()
	{
		open(path, openMode);
	}

	inline BinaryWriter::operator bool() const noexcept
	{
		return isOpen();
	}

# if __cpp_lib_concepts
	template <Concept::TriviallyCopyable Type>
# else
	template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>*>
# endif
	inline bool BinaryWriter::write(const Type& src)
	{
		return (write(std::addressof(src), sizeof(Type)) == sizeof(Type));
	}
}
