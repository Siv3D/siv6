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
# include "PointVector.hpp"

namespace s3d
{
	namespace Cursor
	{
		[[nodiscard]]
		Point Pos();

		[[nodiscard]]
		Point PreviousPos();

		[[nodiscard]]
		Point Delta();

		[[nodiscard]]
		Vec2 PosF();

		[[nodiscard]]
		Vec2 PreviousPosF();

		[[nodiscard]]
		Vec2 DeltaF();

		[[nodiscard]]
		Point PosRaw();

		[[nodiscard]]
		Point PreviousPosRaw();

		[[nodiscard]]
		Point DeltaRaw();
	}
}