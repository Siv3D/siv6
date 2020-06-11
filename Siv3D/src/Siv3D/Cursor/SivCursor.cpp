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

# include <Siv3D/Cursor.hpp>
# include <Siv3D/Cursor/ICursor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Cursor
	{
		Point Pos()
		{
			return SIV3D_ENGINE(Cursor)->getState().current;
		}

		Point PreviousPos()
		{
			return SIV3D_ENGINE(Cursor)->getState().previous;
		}

		Point Delta()
		{
			return SIV3D_ENGINE(Cursor)->getState().delta;
		}

		Vec2 PosF()
		{
			return SIV3D_ENGINE(Cursor)->getState().currentF;
		}

		Vec2 PreviousPosF()
		{
			return SIV3D_ENGINE(Cursor)->getState().previousF;
		}

		Vec2 DeltaF()
		{
			return SIV3D_ENGINE(Cursor)->getState().deltaF;
		}

		Point PosRaw()
		{
			return SIV3D_ENGINE(Cursor)->getState().currentRaw;
		}

		Point PreviousPosRaw()
		{
			return SIV3D_ENGINE(Cursor)->getState().previousRaw;
		}

		Point DeltaRaw()
		{
			return SIV3D_ENGINE(Cursor)->getState().deltaRaw;
		}
	}
}
