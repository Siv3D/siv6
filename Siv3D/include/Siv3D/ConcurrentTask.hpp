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
# ifndef SIV3D_NO_CONCURRENT_API

# include <future>
# include <type_traits>
# include "Platform.hpp"

namespace s3d
{
	template <class Type>
	class ConcurrentTask : protected std::future<Type>
	{
	private:

		using base_type = std::future<Type>;

	public:

		using base_type::operator=;
		using base_type::get;
		using base_type::valid;
		using base_type::wait;
		using base_type::wait_for;
		using base_type::wait_until;
		using base_type::share;

		ConcurrentTask() = default;

		template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>* = nullptr>
		explicit ConcurrentTask(Fty&& f, Args&&... args)
			: std::future<Type>(std::async(std::launch::async, std::forward<Fty>(f), std::forward<Args>(args)...)) {}

		[[nodiscard]]
		bool isReady() const
		{
			return base_type::valid()
				&& (base_type::wait_for(std::chrono::seconds(0)) == std::future_status::ready);
		}
	};

	template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>* = nullptr>
	ConcurrentTask(Fty, Args...)->ConcurrentTask<std::invoke_result_t<std::decay_t<Fty>, std::decay_t<Args>...>>;

	template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>* = nullptr>
	[[nodiscard]]
	inline auto CreateConcurrentTask(Fty&& f, Args&&... args)
	{
		return ConcurrentTask<std::invoke_result_t<std::decay_t<Fty>, std::decay_t<Args>...>>(std::forward<Fty>(f), std::forward<Args>(args)...);
	}
}

# endif
