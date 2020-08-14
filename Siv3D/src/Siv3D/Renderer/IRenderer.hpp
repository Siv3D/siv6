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
# include <Siv3D/Common.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/ResizeMode.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DRenderer
	{
	public:

		static ISiv3DRenderer* Create();

		virtual ~ISiv3DRenderer() = default;

		virtual void init() = 0;

		virtual StringView getName() const = 0;

		virtual void clear() = 0;

		virtual void flush() = 0;

		virtual bool present() = 0;

		virtual void setSceneResizeMode(ResizeMode resizeMode) = 0;

		virtual ResizeMode getSceneResizeMode() const noexcept;

		virtual void setSceneBufferSize(Size size) = 0;

		virtual Size getSceneBufferSize() const noexcept = 0;
	};
}
