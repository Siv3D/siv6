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
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class ISiv3DLogger
	{
	public:

		static ISiv3DLogger* Create();

		virtual ~ISiv3DLogger() = default;

		virtual void write(LogType type, StringView s) = 0;
	};
}
