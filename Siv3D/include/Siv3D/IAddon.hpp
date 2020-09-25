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
	class IAddon
	{
	public:

		virtual ~IAddon() = default;

		virtual bool init() = 0;

		virtual bool update() = 0;

		virtual void draw() const {}
	};
}
