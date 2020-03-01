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
# include <tuple>
# include "Siv3DComponent.hpp"

namespace s3d
{
	class ISiv3DDummy;

	class Siv3DEngine
	{
	private:

		inline static Siv3DEngine* pEngine = nullptr;

		std::tuple<Siv3DComponent<ISiv3DDummy>> m_components;

	public:

		Siv3DEngine();

		~Siv3DEngine();

		[[nodiscard]]
		static bool isActive() noexcept;

		template <class Interface>
		[[nodiscard]]
		static auto* Get()
		{
			return std::get<Siv3DComponent<Interface>>(pEngine->m_components).get();
		}
	};
}
