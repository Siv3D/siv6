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
	enum class LogType;
	class StringView;

	class ISiv3DLogger
	{
	public:

		static ISiv3DLogger* Create();

		virtual ~ISiv3DLogger() = default;

		virtual void write(LogType type, StringView s) = 0;
	};
}
