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
# include <Siv3D/Array.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Cursor/ICursor.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

namespace s3d
{
	class CCursor final : public ISiv3DCursor
	{
	private:

		GLFWwindow* m_window = nullptr;

		CursorState m_state;

		HashTable<String, GLFWcursor*> m_customCursors;

	public:

		CCursor();

		~CCursor() override;

		void init() override;

		bool update() override;
		
		const CursorState& getState() const noexcept override;

		bool registerCursor(StringView name, const Image& image, const Point& hotSpot) override;

		void requestStyle(StringView name) override;
	};
}
