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
# include <type_traits>
# include <memory>
# include <utility>

namespace s3d
{
	namespace detail
	{
		template <class Tag, class... Args>
		struct NamedParameterInternal
		{
			std::tuple<Args...> tuple;
		};
	}

	template <class Tag, class Type>
	class NamedParameter
	{
	public:

		static_assert(std::is_object_v<Type>
			&& std::is_destructible_v<Type>
			&& not std::is_array_v<Type>);

		using value_type = Type;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;

		template <class U, std::enable_if_t<std::is_constructible_v<value_type, U>>* = nullptr>
		constexpr NamedParameter(const NamedParameter<Tag, U>& holder) noexcept(std::is_nothrow_constructible_v<value_type, U>)
			: m_value(holder.value()) {}

		template <class... Args>
		constexpr NamedParameter(const detail::NamedParameterInternal<Tag, Args...>& parameters)
			: m_value(std::make_from_tuple<value_type>(parameters.tuple)) {}

		[[nodiscard]]
		constexpr pointer operator ->() noexcept
		{
			return std::addressof(m_value);
		}

		[[nodiscard]]
		constexpr const_pointer operator ->() const noexcept
		{
			return std::addressof(m_value);
		}

		[[nodiscard]]
		constexpr reference operator *() noexcept
		{
			return m_value;
		}

		[[nodiscard]]
		constexpr const_reference operator *() const noexcept
		{
			return m_value;
		}

		[[nodiscard]]
		constexpr reference value() noexcept
		{
			return m_value;
		}

		[[nodiscard]]
		constexpr const_reference value() const noexcept
		{
			return m_value;
		}

	private:

		value_type m_value;
	};

	template <class Tag>
	struct NamedParameterHelper
	{
		template <class Type>
		[[nodiscard]]
		constexpr auto operator =(Type&& value) const noexcept
		{
			return detail::NamedParameterInternal<Tag, Type>
				{ std::forward_as_tuple(std::forward<Type>(value)) };
		}

		template <class... Args>
		[[nodiscard]]
		constexpr auto operator ()(Args&&... args) const noexcept
		{
			return detail::NamedParameterInternal<Tag, Args...>
				{ std::forward_as_tuple(std::forward<Args>(args)...) };
		}
	};
}

# define SIV3D_NAMED_PARAMETER(name) \
inline constexpr auto name = s3d::NamedParameterHelper<struct name##_tag>{};\
template <class Type> using name##_ = s3d::NamedParameter<struct name##_tag, Type>
