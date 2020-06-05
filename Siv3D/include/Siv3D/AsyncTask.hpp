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
	/// @brief 非同期処理クラス
	/// @tparam Type 処理の戻り値の型
	template <class Type>
	class AsyncTask : protected std::future<Type>
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

		SIV3D_NODISCARD_CXX20
		AsyncTask() = default;

		template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		explicit AsyncTask(Fty&& f, Args&&... args);

		[[nodiscard]]
		bool isReady() const;
	};

	template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>* = nullptr>
	AsyncTask(Fty, Args...)->AsyncTask<std::invoke_result_t<std::decay_t<Fty>, std::decay_t<Args>...>>;

	template <class Fty, class... Args, std::enable_if_t<std::is_invocable_v<Fty, Args...>>* = nullptr>
	[[nodiscard]]
	inline auto CreateAsyncTask(Fty&& f, Args&&... args);
}

# include "detail/AsyncTask.ipp"

# endif // SIV3D_NO_CONCURRENT_API
