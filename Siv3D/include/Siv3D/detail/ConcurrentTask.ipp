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

namespace s3d
{
	template <class Type>
	template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>*>
	inline ConcurrentTask<Type>::ConcurrentTask(Fty&& f, Args&&... args)
		: std::future<Type>(std::async(std::launch::async, std::forward<Fty>(f), std::forward<Args>(args)...)) {}

	template <class Type>
	inline bool ConcurrentTask<Type>::isReady() const
	{
		return base_type::valid()
			&& (base_type::wait_for(std::chrono::seconds(0)) == std::future_status::ready);
	}

	template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>*>
	inline auto CreateConcurrentTask(Fty&& f, Args&&... args)
	{
		return ConcurrentTask<std::invoke_result_t<std::decay_t<Fty>, std::decay_t<Args>...>>(std::forward<Fty>(f), std::forward<Args>(args)...);
	}
}
