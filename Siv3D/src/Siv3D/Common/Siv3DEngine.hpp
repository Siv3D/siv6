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
	class ISiv3DLogger;
	class ISiv3DSystem;
	class ISiv3DProfiler;
	class ISiv3DUserAction;
	class ISiv3DWindow;
	class ISiv3DImageDecoder;
	class ISiv3DScene;
	class ISiv3DConsole;
	class ISiv3DCursor;
	class ISiv3DRenderer;
	class ISiv3DRenderer2D;

	class Siv3DEngine
	{
	private:

		inline static Siv3DEngine* pEngine = nullptr;

		std::tuple<
			Siv3DComponent<ISiv3DDummy>,
			Siv3DComponent<ISiv3DLogger>,
			Siv3DComponent<ISiv3DSystem>,
			Siv3DComponent<ISiv3DProfiler>,
			Siv3DComponent<ISiv3DUserAction>,
			Siv3DComponent<ISiv3DWindow>,
			Siv3DComponent<ISiv3DImageDecoder>,
			Siv3DComponent<ISiv3DScene>,
			Siv3DComponent<ISiv3DConsole>,
			Siv3DComponent<ISiv3DCursor>,
			Siv3DComponent<ISiv3DRenderer>,
			Siv3DComponent<ISiv3DRenderer2D>> m_components;

	public:

		Siv3DEngine();

		~Siv3DEngine();

		[[nodiscard]]
		static bool isActive() noexcept;

		template <class Interface>
		[[nodiscard]]
		static auto* Get() noexcept
		{
			return std::get<Siv3DComponent<Interface>>(pEngine->m_components).get();
		}
	};

	# define SIV3D_ENGINE(COMPONENT) Siv3DEngine::Get<ISiv3D##COMPONENT>()
}
