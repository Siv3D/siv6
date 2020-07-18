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
# include "String.hpp"
# include "Optional.hpp"
# include "DateTime.hpp"
# include "Array.hpp"
# include "SpecialFolder.hpp"

namespace s3d
{
	namespace Platform
	{
	# if SIV3D_PLATFORM(WINDOWS)

		using NativeFilePath = std::wstring;

	# else

		using NativeFilePath = std::string;

	# endif
	}

	namespace FileSystem
	{
		/// @brief ファイルパスがリソースのパスであるかを返します。
		/// @param path ファイルパス
		/// @return リソースのパスである場合は true, それ以外の場合は false
		[[nodiscard]]
		bool IsResourcePath(FilePathView path) noexcept;

		/// @brief 
		/// @param path 
		/// @return 
		[[nodiscard]]
		bool Exists(FilePathView path);

		/// @brief 
		/// @param path 
		/// @return 
		[[nodiscard]]
		bool IsDirectory(FilePathView path);
		
		/// @brief 
		/// @param path 
		/// @return 
		[[nodiscard]]
		bool IsFile(FilePathView path);

		/// @brief 
		/// @param path 
		/// @return 
		[[nodiscard]]
		bool IsResource(FilePathView path);

		/// @brief 絶対パスを返します。
		/// @param path パス
		/// @remarks 実際に存在するファイルやディレクトリのパスである必要はありません
		/// @return ファイルの絶対パス。失敗した場合は空の文字列
		[[nodiscard]]
		FilePath FullPath(FilePathView path);

		/// @brief 
		/// @param path 
		/// @return 
		[[nodiscard]]
		Platform::NativeFilePath NativePath(FilePathView path);

		/// @brief 
		/// @param path 
		/// @return 
		[[nodiscard]]
		String Extension(FilePathView path);

		/// @brief 
		/// @param path 
		/// @return 
		[[nodiscard]]
		String FileName(FilePathView path);

		/// @brief 
		/// @param path 
		/// @return 
		[[nodiscard]]
		String BaseName(FilePathView path);

		[[nodiscard]]
		FilePath ParentPath(FilePathView path, size_t level = 0);

		[[nodiscard]]
		FilePath ParentPath(FilePathView path, size_t level, FilePath& baseFullPath);

		[[nodiscard]]
		FilePath VolumePath(FilePathView path);

		[[nodiscard]]
		bool IsEmptyDirectory(FilePathView path);

		[[nodiscard]]
		int64 Size(FilePathView path);

		/// @brief ファイルのサイズを返します。
		/// @param path ファイルパス
		/// @remarks ファイルが存在しなかったり、空である場合は 0 を返します。
		/// @return ファイルのサイズ
		[[nodiscard]]
		int64 FileSize(FilePathView path);

		[[nodiscard]]
		Optional<DateTime> CreationTime(FilePathView path);

		[[nodiscard]]
		Optional<DateTime> WriteTime(FilePathView path);

		[[nodiscard]]
		Optional<DateTime> AccessTime(FilePathView path);

		[[nodiscard]]
		Array<FilePath> DirectoryContents(FilePathView path, bool recursive = true);

		[[nodiscard]]
		const FilePath& InitialDirectory() noexcept;

		[[nodiscard]]
		const FilePath& ModulePath() noexcept;

		[[nodiscard]]
		FilePath CurrentDirectory();

		bool ChangeCurrentDirectory(FilePathView path);

		[[nodiscard]]
		FilePath GetFolderPath(SpecialFolder folder);

		[[nodiscard]]
		FilePath TemporaryDirectoryPath();

		[[nodiscard]]
		FilePath UniqueFilePath(FilePathView directory = TemporaryDirectoryPath());

		[[nodiscard]]
		FilePath RelativePath(FilePathView path, FilePathView start = FileSystem::CurrentDirectory());

		bool CreateDirectories(FilePathView path);

		bool CreateParentDirectories(FilePathView path);
	}
}
