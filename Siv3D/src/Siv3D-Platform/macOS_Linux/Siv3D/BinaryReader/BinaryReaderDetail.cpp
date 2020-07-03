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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/FormatUtility.hpp>
# include "BinaryReaderDetail.hpp"

namespace s3d
{
	BinaryReader::BinaryReaderDetail::BinaryReaderDetail()
	{

	}

	BinaryReader::BinaryReaderDetail::~BinaryReaderDetail()
	{
		close();
	}

	bool BinaryReader::BinaryReaderDetail::open(const FilePathView path, const OpenMode openMode)
	{
		LOG_TRACE(U"BinaryReader::BinaryReaderDetail::open(\"{0}\", {1})"_fmt(
			path, FromEnum(openMode)));

		close();

		FILE* file = std::fopen(path.narrow().c_str(), "r");
		
		if (not file) SIV3D_UNLIKELY
		{
			LOG_FAIL(U"❌ BinaryReader: Failed to open the file `{0}`"_fmt(
				path));
			return false;
		}
		
		m_file =
		{
			.file = file
		};

		m_info =
		{
			.isOpen		= true,
			.size		= FileSystem::FileSize(path),
			.fullPath	= FileSystem::FullPath(path)
		};

		LOG_INFO(U"📤 BinaryReader: File `{0}` opened (size: {1})"_fmt(
			m_info.fullPath, FormatDataSize(m_info.size)));

		return true;
	}

	void BinaryReader::BinaryReaderDetail::close()
	{
		if (!m_info.isOpen) SIV3D_UNLIKELY
		{
			return;
		}

		std::fclose(m_file.file);
		LOG_INFO(U"📥 BinaryReader: File `{0}` closed"_fmt(
			m_info.fullPath));
		
		m_file = {};

		m_info = {};
	}

	bool BinaryReader::BinaryReaderDetail::isOpen() const noexcept
	{
		return m_info.isOpen;
	}

	int64 BinaryReader::BinaryReaderDetail::size() const noexcept
	{
		return m_info.size;
	}

	int64 BinaryReader::BinaryReaderDetail::setPos(const int64 pos)
	{
		if (!m_info.isOpen) SIV3D_UNLIKELY
		{
			return 0;
		}
		
		std::fseek(m_file.file, pos, SEEK_SET);
		
		return std::ftell(m_file.file);
	}

	int64 BinaryReader::BinaryReaderDetail::getPos()
	{
		if (!m_info.isOpen) SIV3D_UNLIKELY
		{
			return 0;
		}
		
		return std::ftell(m_file.file);
	}

	int64 BinaryReader::BinaryReaderDetail::read(const NonNull<void*> buffer, const int64 size)
	{
		if (!m_info.isOpen) SIV3D_UNLIKELY
		{
			return 0;
		}

		return std::fread(buffer.pointer, 1, size, m_file.file);
	}

	int64 BinaryReader::BinaryReaderDetail::read(const NonNull<void*> buffer, const int64 pos, const int64 size)
	{
		if (!m_info.isOpen) SIV3D_UNLIKELY
		{
			return 0;
		}
	
		setPos(pos);
		
		return std::fread(buffer.pointer, 1, size, m_file.file);
	}

	int64 BinaryReader::BinaryReaderDetail::lookahead(const NonNull<void*> buffer, const int64 size)
	{
		if (!m_info.isOpen) SIV3D_UNLIKELY
		{
			return 0;
		}

		const auto previousPos = getPos();
		
		const auto readBytes = std::fread(buffer.pointer, 1, size, m_file.file);
		
		setPos(previousPos);
		
		return readBytes;
	}

	int64 BinaryReader::BinaryReaderDetail::lookahead(const NonNull<void*> buffer, const int64 pos, const int64 size)
	{
		if (!m_info.isOpen) SIV3D_UNLIKELY
		{
			return 0;
		}

		const auto previousPos = getPos();
		
		setPos(pos);
		
		const auto readBytes = std::fread(buffer.pointer, 1, size, m_file.file);
		
		setPos(previousPos);
		
		return readBytes;
	}

	const FilePath& BinaryReader::BinaryReaderDetail::path() const noexcept
	{
		return m_info.fullPath;
	}
}
