//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files(the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions :
//	
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//	
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
//
//----------------------------------------------------------------------------------------

# pragma once
# ifndef SIV3D_INCLUDED
#	define SIV3D_INCLUDED
# endif

//////////////////////////////////////////////////
//
// Utilities
//
//////////////////////////////////////////////////

// プラットフォーム
// Platform
# include <Siv3D/Platform.hpp>

// ライブラリのバージョン
// Library version
# include <Siv3D/Version.hpp>

// 基本型
// Types
# include <Siv3D/Types.hpp>

// 前方宣言
// Forward declarations
# include <Siv3D/Fwd.hpp>

// プレースホルダー
// Place holder
# include <Siv3D/PlaceHolder.hpp>

// コピー禁止 Mixin
// Non-copyable mixin
# include <Siv3D/Uncopyable.hpp>

// 名前付き引数
// Named parameter
# include <Siv3D/NamedParameter.hpp>

// 定義済み名前付き引数
// Predefined named parameters
# include <Siv3D/PredefinedNamedParameter.hpp>

// 範囲をインデックス値とセットで列挙するユーティリティー
// Indexed iterator
# include <Siv3D/Indexed.hpp>

// メタ関数
// Meta
//# include <Siv3D/Meta.hpp>

// 型特性
// Type traits
//# include <Siv3D/TypeTraits.hpp>

// ユーティリティー
// Utilities
# include <Siv3D/Utility.hpp>

# include <Siv3D/StringView.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Unicode.hpp>

# include <Siv3D/Array.hpp>

# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/IntFormatter.hpp>
# include <Siv3D/FormatInt.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/FormatData.hpp>
# include <Siv3D/Format.hpp>


# include <Siv3D/Error.hpp>

# include <Siv3D/ApplicationOptions.hpp>

# include <Siv3D/Time.hpp>


# include <Siv3D/LogLevel.hpp>
# include <Siv3D/LogType.hpp>
# include <Siv3D/Logger.hpp>


# include <Siv3D/Console.hpp>

# if !defined(SIV3D_LIBRARY_BUILD) && SIV3D_PLATFORM(WINDOWS)

	# include <Siv3D/Windows/Libraries.hpp>

# endif


# if !defined(SIV3D_LIBRARY_BUILD) && !defined(NO_S3D_USING)

using namespace s3d;
using namespace std::literals;

# endif
