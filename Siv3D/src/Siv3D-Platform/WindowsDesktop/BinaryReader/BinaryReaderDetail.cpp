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

# include <cassert>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FormatUtility.hpp>
# include "BinaryReaderDetail.hpp"

namespace s3d
{
	namespace detail
	{
		inline constexpr DWORD MakeFlag(const OpenMode openMode) noexcept
		{
			DWORD flagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
			
			if (openMode & OpenMode::RandomAccess)
			{
				flagsAndAttributes |= FILE_FLAG_RANDOM_ACCESS;
			}

			if (openMode & OpenMode::SequentialScan)
			{
				flagsAndAttributes |= FILE_FLAG_SEQUENTIAL_SCAN;
			}
			
			return flagsAndAttributes;
		}

		inline OVERLAPPED MakeOffset(const int64 offset)
		{
			const ULARGE_INTEGER i = { .QuadPart = static_cast<uint64>(offset) };
			return OVERLAPPED
			{
				.Offset		= i.LowPart,
				.OffsetHigh	= i.HighPart,
			};
		}
	}

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

		if (const bool isResource = false; isResource)
		{
			HMODULE hModule = ::GetModuleHandleW(nullptr);
			const std::wstring pathW = path.toWstr();

			if (HRSRC hrs = ::FindResourceW(hModule, &pathW[1], L"FILE")) [[likely]]
			{
				m_resource =
				{
					.pointer = static_cast<const Byte*>(::LockResource(::LoadResource(hModule, hrs)))
				};

				m_info =
				{
					.isOpen		= true,
					.size		= ::SizeofResource(hModule, hrs),
					.fullPath	= FilePath(path)
				};

				LOG_INFO(U"📤 BinaryReader: Opened resource \"{0}\" size: {1}"_fmt(
					m_info.fullPath, FormatDataSize(m_info.size)));

				return true;
			}
			else
			{
				LOG_FAIL(U"❌ BinaryReader: Failed to open resource \"{0}\""_fmt(
					path));
				return false;
			}
		}
		else
		{
			// ファイルのオープン
			{
				const HANDLE handle = ::CreateFileW(path.toWstr().c_str(),
					GENERIC_READ,
					(FILE_SHARE_READ | FILE_SHARE_WRITE),
					nullptr,
					OPEN_EXISTING,
					detail::MakeFlag(openMode),
					nullptr);

				if (handle == INVALID_HANDLE_VALUE) [[unlikely]]
				{
					LOG_FAIL(U"❌ BinaryReader: Failed to open the file `{0}`. {1}"_fmt(
						path, Platform::Windows::GetLastErrorMessage()));
					return false;
				}

				m_file =
				{
					.handle = handle
				};
			}

			// ファイルのサイズ
			LARGE_INTEGER size;
			{
				if (!::GetFileSizeEx(m_file.handle, &size)) [[unlikely]]
				{
					LOG_FAIL(U"❌ BinaryReader: GetFileSizeEx() failed. {0}"_fmt(
						Platform::Windows::GetLastErrorMessage()));
					return false;
				}
			}

			m_info =
			{
				.isOpen		= true,
				.size		= size.QuadPart,
				.fullPath	= FilePath(path)
			};

			LOG_INFO(U"📤 BinaryReader: File `{0}` opened (size: {1})"_fmt(
				m_info.fullPath, FormatDataSize(m_info.size)));
		}

		return true;
	}

	void BinaryReader::BinaryReaderDetail::close()
	{
		if (!m_info.isOpen) [[unlikely]]
		{
			return;
		}

		if (isResource())
		{
			m_resource = {};
			LOG_INFO(U"📥 BinaryReader: Resource `{0}` closed"_fmt(
				m_info.fullPath));
		}
		else
		{
			::CloseHandle(m_file.handle);		
			m_file = {};
			LOG_INFO(U"📥 BinaryReader: File `{0}` closed"_fmt(
				m_info.fullPath));
		}

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

	int64 BinaryReader::BinaryReaderDetail::setPos(const int64 clampedPos)
	{
		if (!m_info.isOpen) [[unlikely]]
		{
			return 0;
		}

		assert(InRange<int64>(clampedPos, 0, size()));

		if (isResource())
		{
			return (m_resource.pos = clampedPos);
		}
		else
		{
			const LARGE_INTEGER distance = { .QuadPart = clampedPos };
			LARGE_INTEGER newPos;
			::SetFilePointerEx(m_file.handle, distance, &newPos, FILE_BEGIN);
			return newPos.QuadPart;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::getPos()
	{
		if (!m_info.isOpen) [[unlikely]]
		{
			return 0;
		}

		if (isResource())
		{
			return m_resource.pos;
		}
		else
		{
			const LARGE_INTEGER distance = { .QuadPart = 0 };
			LARGE_INTEGER currentPos;
			::SetFilePointerEx(m_file.handle, distance, &currentPos, FILE_CURRENT);
			return currentPos.QuadPart;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::read(const NonNull<void*> buffer, const int64 size)
	{
		if (!m_info.isOpen) [[unlikely]]
		{
			return 0;
		}

		if (isResource())
		{
			const int64 readBytes = Clamp(size, 0LL, (m_info.size - m_resource.pos));
			std::memcpy(buffer.pointer, (m_resource.pointer + m_resource.pos), static_cast<size_t>(readBytes));
			m_resource.pos += readBytes;
			return readBytes;
		}
		else
		{
			DWORD readBytes;

			if (!::ReadFile(m_file.handle, buffer.pointer, static_cast<DWORD>(size), &readBytes, nullptr)) [[unlikely]]
			{
				LOG_FAIL(U"❌ BinaryReader `{0}`: ReadFile() failed. {1}"_fmt(
					m_info.fullPath, Platform::Windows::GetLastErrorMessage()));
				return 0;
			}

			return readBytes;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::read(const NonNull<void*> buffer, const int64 pos, const int64 size)
	{
		if (!m_info.isOpen) [[unlikely]]
		{
			return 0;
		}

		if (isResource())
		{
			const int64 readBytes = Clamp(size, 0LL, (m_info.size - pos));
			std::memcpy(buffer.pointer, (m_resource.pointer + pos), static_cast<size_t>(readBytes));
			m_resource.pos = (pos + readBytes);
			return readBytes;
		}
		else
		{
			OVERLAPPED overlapped = detail::MakeOffset(pos);
			DWORD readBytes;

			if (!::ReadFile(m_file.handle, buffer.pointer, static_cast<DWORD>(size), &readBytes, &overlapped)) [[unlikely]]
			{
				LOG_FAIL(U"❌ BinaryReader `{0}`: ReadFile() failed. {1}"_fmt(
					m_info.fullPath, Platform::Windows::GetLastErrorMessage()));
				return 0;
			}

			return readBytes;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::lookahead(const NonNull<void*> buffer, const int64 size)
	{
		if (!m_info.isOpen) [[unlikely]]
		{
			return 0;
		}

		if (isResource())
		{
			const int64 readBytes = Clamp(size, 0LL, (m_info.size - m_resource.pos));
			std::memcpy(buffer.pointer, (m_resource.pointer + m_resource.pos), static_cast<size_t>(readBytes));
			return readBytes;
		}
		else
		{
			const auto previousPos = getPos();
			DWORD readBytes;

			if (!::ReadFile(m_file.handle, buffer.pointer, static_cast<DWORD>(size), &readBytes, nullptr)) [[unlikely]]
			{
				LOG_FAIL(U"❌ BinaryReader `{0}`: ReadFile() failed. {1}"_fmt(
					m_info.fullPath, Platform::Windows::GetLastErrorMessage()));
				return 0;
			}

			setPos(previousPos);
			return readBytes;
		}
	}

	int64 BinaryReader::BinaryReaderDetail::lookahead(const NonNull<void*> buffer, const int64 pos, const int64 size)
	{
		if (!m_info.isOpen) [[unlikely]]
		{
			return 0;
		}

		if (isResource())
		{
			const int64 readBytes = Clamp(size, 0LL, (m_info.size - pos));
			std::memcpy(buffer.pointer, (m_resource.pointer + pos), static_cast<size_t>(readBytes));
			return readBytes;
		}
		else
		{
			const auto previousPos = getPos();
			OVERLAPPED overlapped = detail::MakeOffset(pos);
			DWORD readBytes;

			if (!::ReadFile(m_file.handle, buffer.pointer, static_cast<DWORD>(size), &readBytes, &overlapped)) [[unlikely]]
			{
				LOG_FAIL(U"❌ BinaryReader `{0}`: ReadFile() failed. {1}"_fmt(
					m_info.fullPath, Platform::Windows::GetLastErrorMessage()));
				return 0;
			}

			setPos(previousPos);
			return readBytes;
		}
	}

	const FilePath& BinaryReader::BinaryReaderDetail::path() const noexcept
	{
		return m_info.fullPath;
	}

	bool BinaryReader::BinaryReaderDetail::isResource() const noexcept
	{
		return (m_resource.pointer != nullptr);
	}
}
