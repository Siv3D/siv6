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
	class ISiv3DConsole
	{
	public:

		static ISiv3DConsole* Create();

		virtual ~ISiv3DConsole() = default;

		virtual void open() = 0;

		virtual void close() = 0;
	};
}
