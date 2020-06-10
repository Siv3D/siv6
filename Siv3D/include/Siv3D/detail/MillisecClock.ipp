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
	uint64 MillisecClock::ms() const noexcept
	{
		return (Time::GetMillisec() - m_start);
	}

	/// @brief ログに経過時間を出力します。
	void MillisecClock::log() const
	{
		Logger(Milliseconds(ms()));
	}

	/// @brief 経過時間をデバッグ表示します。
	//void MillisecClock::print() const
	//{
	//	Print(Milliseconds(ms()));
	//}
}
