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

//////////////////////////////////////////////////////////////////////////////
//
//	Copyright (C) 2011 - 2017 Andrzej Krzemienski.
//
//	Use, modification, and distribution is subject to the Boost Software
//	License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//	http://www.boost.org/LICENSE_1_0.txt)
//

namespace s3d
{
	namespace detail
	{
		inline constexpr struct TrivialInit_t {} TrivialInit{};

		template <class U>
		constexpr U convert(U v)
		{
			return v;
		}

		namespace swap_ns
		{
			using std::swap;

			template <class T>
			void adl_swap(T& t, T& u) noexcept(noexcept(swap(t, u)))
			{
				swap(t, u);
			}
		}

		template <class Type>
		union Storage_t
		{
			unsigned char dummy_;

			Type value_;

			constexpr Storage_t(TrivialInit_t) noexcept
				: dummy_() {};

			template <class... Args>
			constexpr Storage_t(Args&&... args)
				: value_(std::forward<Args>(args)...) {}

			~Storage_t() {}
		};

		template <class Type>
		union Constexpr_storage_t
		{
			unsigned char dummy_;

			Type value_;

			constexpr Constexpr_storage_t(TrivialInit_t) noexcept
				: dummy_() {};

			template <class... Args>
			constexpr Constexpr_storage_t(Args&&... args)
				: value_(std::forward<Args>(args)...) {}

			~Constexpr_storage_t() = default;
		};

		template <class Type>
		struct optional_base
		{
			bool init_;

			Storage_t<Type> storage_;

			constexpr optional_base() noexcept
				: init_(false)
				, storage_(TrivialInit) {};

			explicit constexpr optional_base(const Type& v)
				: init_(true)
				, storage_(v) {}

			explicit constexpr optional_base(Type&& v)
				: init_(true)
				, storage_(std::move(v)) {}

			template <class... Args> explicit optional_base(InPlace_t, Args&&... args)
				: init_(true)
				, storage_(std::forward<Args>(args)...) {}

			template <class U, class... Args, std::enable_if_t<std::is_constructible_v<Type, std::initializer_list<U>>>* = nullptr>
			explicit optional_base(InPlace_t, std::initializer_list<U> il, Args&&... args)
				: init_(true)
				, storage_(il, std::forward<Args>(args)...) {}

			~optional_base()
			{
				if (init_)
				{
					storage_.value_.~Type();
				}
			}
		};

		template <class Type>
		struct constexpr_optional_base
		{
			bool init_;

			Constexpr_storage_t<Type> storage_;

			constexpr constexpr_optional_base() noexcept
				: init_(false)
				, storage_(TrivialInit) {};

			explicit constexpr constexpr_optional_base(const Type& v)
				: init_(true)
				, storage_(v) {}

			explicit constexpr constexpr_optional_base(Type&& v)
				: init_(true)
				, storage_(std::move(v)) {}

			template <class... Args> explicit constexpr constexpr_optional_base(InPlace_t, Args&&... args)
				: init_(true)
				, storage_(std::forward<Args>(args)...) {}

			template <class U, class... Args, std::enable_if_t<std::is_constructible_v<Type, std::initializer_list<U>>>* = nullptr>
			explicit constexpr constexpr_optional_base(InPlace_t, std::initializer_list<U> il, Args&&... args)
				: init_(true)
				, storage_(il, std::forward<Args>(args)...) {}

			~constexpr_optional_base() = default;
		};
	}

	template <class Type>
	using OptionalBase = std::conditional_t<std::is_trivially_destructible_v<Type>, detail::constexpr_optional_base<typename std::remove_const_t<Type>>, detail::optional_base<typename std::remove_const_t<Type>>>;
}
