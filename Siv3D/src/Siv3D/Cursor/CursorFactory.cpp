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

# include <Cursor/CCursor.hpp>
# include <Siv3D/Cursor/CCursor_Null.hpp>
# include <Siv3D/Common/ApplicationOptions.hpp>

namespace s3d
{
	ISiv3DCursor* ISiv3DCursor::Create()
	{
		if (g_ApplicationOptions.headlessMode)
		{
			return new CCursor_Null;
		}
		else
		{
			return new CCursor;
		}
	}
}
