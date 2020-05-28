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

namespace s3d
{
	namespace FileSystem
	{
		/// @brief ファイルパスがリソースのパスであるかを返します。
		/// @param path ファイルパス
		/// @return リソースのパスである場合は true, それ以外の場合は false
		[[nodiscard]]
		bool IsResourcePath(FilePathView path) noexcept;

		/// @brief 絶対パスを返します。
		/// @param path パス
		/// @remarks 実際に存在するファイルやディレクトリのパスである必要はありません
		/// @return ファイルの絶対パス。失敗した場合は空の文字列
		[[nodiscard]]
		FilePath FullPath(FilePathView path);

		/// @brief ファイルのサイズを返します。
		/// @param path ファイルパス
		/// @remarks ファイルが存在しなかったり、空である場合は 0 を返します。
		/// @return ファイルのサイズ
		[[nodiscard]]
		int64 FileSize(FilePathView path);
	}
}
