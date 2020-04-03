﻿//-----------------------------------------------
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
	class ISiv3DRenderer
	{
	public:

		static ISiv3DRenderer* Create();

		virtual ~ISiv3DRenderer() = default;

		virtual void init() = 0;

		virtual void onMainThreadStart() = 0;

		virtual void clear() = 0;

		virtual void flush() = 0;

		virtual bool present() = 0;
	};
}