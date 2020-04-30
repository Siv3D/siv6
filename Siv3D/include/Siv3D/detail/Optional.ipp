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
	template <class Type>
	inline Type* Optional<Type>::dataptr()
	{
		return std::addressof(OptionalBase<Type>::storage_.value_);
	}

	template <class Type>
	inline constexpr const Type* Optional<Type>::dataptr() const
	{
		return std::addressof(OptionalBase<Type>::storage_.value_);
	}

	template <class Type>
	inline constexpr const Type& Optional<Type>::contained_val() const&
	{
		return OptionalBase<Type>::storage_.value_;
	}

	template <class Type>
	inline Type& Optional<Type>::contained_val()&
	{
		return OptionalBase<Type>::storage_.value_;
	}

	template <class Type>
	inline Type&& Optional<Type>::contained_val()&&
	{
		return std::move(OptionalBase<Type>::storage_.value_);
	}

	template <class Type>
	inline void Optional<Type>::clear() noexcept
	{
		if (has_value())
		{
			dataptr()->~Type();
		}

		OptionalBase<Type>::init_ = false;
	}

	template <class Type>
	template <class... Args>
	inline void Optional<Type>::initialize(Args&&... args) noexcept(noexcept(Type(std::forward<Args>(args)...)))
	{
		assert(!OptionalBase<Type>::init_);
		::new (static_cast<void*>(dataptr())) Type(std::forward<Args>(args)...);
		OptionalBase<Type>::init_ = true;
	}

	template <class Type>
	template <class U, class... Args>
	inline void Optional<Type>::initialize(std::initializer_list<U> il, Args&&... args) noexcept(noexcept(Type(il, std::forward<Args>(args)...)))
	{
		assert(!OptionalBase<Type>::init_);
		::new (static_cast<void*>(dataptr())) Type(il, std::forward<Args>(args)...);
		OptionalBase<Type>::init_ = true;
	}

	template <class Type>
	inline constexpr Optional<Type>::Optional() noexcept
		: OptionalBase<Type>() {};

	template <class Type>
	inline constexpr Optional<Type>::Optional(None_t) noexcept
		: OptionalBase<Type>() {};

	template <class Type>
	inline Optional<Type>::Optional(const Optional& rhs)
		: OptionalBase<Type>()
	{
		if (rhs.has_value())
		{
			::new (static_cast<void*>(dataptr())) Type(*rhs);
			OptionalBase<Type>::init_ = true;
		}
	}

	template <class Type>
	inline Optional<Type>::Optional(Optional&& rhs) noexcept(std::is_nothrow_move_constructible_v<Type>)
		: OptionalBase<Type>()
	{
		if (rhs.has_value())
		{
			::new (static_cast<void*>(dataptr())) Type(std::move(*rhs));
			OptionalBase<Type>::init_ = true;
		}
	}

	template <class Type>
	inline constexpr Optional<Type>::Optional(const value_type& v)
		: OptionalBase<Type>(v) {}

	template <class Type>
	inline constexpr Optional<Type>::Optional(value_type&& v)
		: OptionalBase<Type>(std::move(v)) {}

	template <class Type>
	template <class... Args>
	inline constexpr Optional<Type>::Optional(InPlace_t, Args&&... args)
		: OptionalBase<Type>(InPlace_t{}, std::forward<Args>(args)...) {}

	template <class Type>
	template <class U, class... Args, std::enable_if_t<std::is_constructible_v<Type, std::initializer_list<U>>>*>
	inline constexpr Optional<Type>::Optional(InPlace_t, std::initializer_list<U> il, Args&&... args)
		: OptionalBase<Type>(InPlace_t{}, il, std::forward<Args>(args)...) {}

	template <class Type>
	inline Optional<Type>& Optional<Type>::operator =(None_t) noexcept
	{
		clear();
		return *this;
	}

	template <class Type>
	inline Optional<Type>& Optional<Type>::operator =(const Optional& rhs)
	{
		if (has_value() == true && rhs.has_value() == false) clear();
		else if (has_value() == false && rhs.has_value() == true) initialize(*rhs);
		else if (has_value() == true && rhs.has_value() == true) contained_val() = *rhs;
		return *this;
	}

	template <class Type>
	inline Optional<Type>& Optional<Type>::operator =(Optional&& rhs) noexcept(std::is_nothrow_move_assignable_v<Type>&& std::is_nothrow_move_constructible_v<Type>)
	{
		if (has_value() == true && rhs.has_value() == false) clear();
		else if (has_value() == false && rhs.has_value() == true) initialize(std::move(*rhs));
		else if (has_value() == true && rhs.has_value() == true) contained_val() = std::move(*rhs);
		return *this;
	}

	template <class Type>
	template <class U, std::enable_if_t<std::is_same_v<std::decay_t<U>, Type>>*>
	inline Optional<Type>& Optional<Type>::operator = (U&& v)
	{
		if (has_value()) { contained_val() = std::forward<U>(v); }
		else { initialize(std::forward<U>(v)); }
		return *this;
	}

	template <class Type>
	template <class... Args>
	inline void Optional<Type>::emplace(Args&&... args)
	{
		clear();
		initialize(std::forward<Args>(args)...);
	}

	template <class Type>
	template <class U, class... Args>
	inline void Optional<Type>::emplace(std::initializer_list<U> il, Args&&... args)
	{
		clear();
		initialize<U, Args...>(il, std::forward<Args>(args)...);
	}

	template <class Type>
	inline void Optional<Type>::swap(Optional<Type>& rhs) noexcept(std::is_nothrow_move_constructible_v<Type> && noexcept(detail::swap_ns::adl_swap(std::declval<Type&>(), std::declval<Type&>())))
	{
		if (has_value() == true && rhs.has_value() == false) { rhs.initialize(std::move(**this)); clear(); }
		else if (has_value() == false && rhs.has_value() == true) { initialize(std::move(*rhs)); rhs.clear(); }
		else if (has_value() == true && rhs.has_value() == true) { using std::swap; swap(**this, *rhs); }
	}

	template <class Type>
	inline constexpr Optional<Type>::operator bool() const noexcept
	{
		return has_value();
	}

	template <class Type>
	inline constexpr bool Optional<Type>::has_value() const noexcept
	{
		return OptionalBase<Type>::init_;
	}

	template <class Type>
	inline constexpr const typename Optional<Type>::value_type* Optional<Type>::operator -> () const
	{
		assert(has_value());
		return dataptr();
	}

	template <class Type>
	inline typename Optional<Type>::value_type* Optional<Type>::operator -> ()
	{
		assert(has_value());
		return dataptr();
	}

	template <class Type>
	inline constexpr typename Optional<Type>::value_type const& Optional<Type>:: operator* () const
	{
		assert(has_value());
		return contained_val();
	}

	template <class Type>
	inline typename Optional<Type>::value_type& Optional<Type>::operator * ()
	{
		assert(has_value());
		return contained_val();
	}

	template <class Type>
	inline constexpr typename Optional<Type>::value_type const& Optional<Type>::value() const
	{
		if (!has_value())
		{
			throw BadOptionalAccess{};
		}

		return contained_val();
	}

	template <class Type>
	inline typename Optional<Type>::value_type& Optional<Type>::value()
	{
		if (!has_value())
		{
			throw BadOptionalAccess{};
		}

		return contained_val();
	}

	template <class Type>
	template <class V>
	inline constexpr typename Optional<Type>::value_type Optional<Type>::value_or(V&& v) const&
	{
		return *this ? **this : detail::convert<Type>(std::forward<V>(v));
	}

	template <class Type>
	template <class V>
	inline typename Optional<Type>::value_type Optional<Type>::value_or(V&& v)&&
	{
		return *this ? std::move(const_cast<Optional<Type>&>(*this).contained_val()) : detail::convert<Type>(std::forward<V>(v));
	}

	template <class Type>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>*>
	inline constexpr typename Optional<Type>::value_type Optional<Type>::value_or_eval(Fty f) const&
	{
		return *this ? **this : f();
	}

	template <class Type>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>*>
	inline typename Optional<Type>::value_type Optional<Type>::value_or_eval(Fty f)&&
	{
		return *this ? std::move(const_cast<Optional<Type>&>(*this).contained_val()) : f();
	}

	template <class Type>
	inline void Optional<Type>::reset() noexcept
	{
		clear();
	}

	template <class Type>
	inline void Optional<Type>::reset(const value_type& v)
	{
		emplace(v);
	}

	template <class Type>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>*>
	inline void Optional<Type>::then(Fty f)
	{
		if (has_value())
		{
			f(contained_val());
		}
	}

	template <class Type>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>*>
	inline void Optional<Type>::then(Fty f) const
	{
		if (has_value())
		{
			f(contained_val());
		}
	}

	template <class Type>
	template <class Fty, class R>
	inline Optional<R> Optional<Type>::map(Fty f)
	{
		if (has_value())
		{
			return f(value());
		}
		else
		{
			return none;
		}
	}

	template <class Type>
	template <class Fty, class R>
	inline Optional<R> Optional<Type>::map(Fty f) const
	{
		if (has_value())
		{
			return f(value());
		}
		else
		{
			return none;
		}
	}


	template <class Type>
	inline constexpr Optional<Type&>::Optional() noexcept
		: ref(nullptr) {}

	template <class Type>
	inline constexpr Optional<Type&>::Optional(None_t) noexcept
		: ref(nullptr) {}

	template <class Type>
	inline constexpr Optional<Type&>::Optional(Type& v) noexcept
		: ref(std::addressof(v)) {}

	template <class Type>
	inline constexpr Optional<Type&>::Optional(const Optional& rhs) noexcept
		: ref(rhs.ref) {}

	template <class Type>
	inline constexpr Optional<Type&>::Optional(InPlace_t, Type& v) noexcept
		: ref(std::addressof(v)) {}

	template <class Type>
	inline Optional<Type&>& Optional<Type&>::operator =(None_t) noexcept
	{
		ref = nullptr;
		return *this;
	}

	template <class Type>
	template <class U, std::enable_if_t<std::is_same_v<std::decay_t<U>, Optional<Type&>>>*>
	inline Optional<Type&>& Optional<Type&>::operator =(U&& rhs) noexcept
	{
		ref = rhs.ref;
		return *this;
	}

	template <class Type>
	inline void Optional<Type&>::emplace(Type& v) noexcept
	{
		ref = std::addressof(v);
	}

	template <class Type>
	inline void Optional<Type&>::swap(Optional<Type&>& rhs) noexcept
	{
		std::swap(ref, rhs.ref);
	}

	template <class Type>
	inline constexpr Optional<Type&>::operator bool() const noexcept
	{
		return has_value();
	}

	template <class Type>
	inline constexpr bool Optional<Type&>::has_value() const noexcept
	{
		return ref != nullptr;
	}

	template <class Type>
	inline constexpr Type* Optional<Type&>::operator ->() const
	{
		assert(ref);
		return ref;
	}

	template <class Type>
	inline constexpr Type& Optional<Type&>::operator *() const
	{
		assert(ref);
		return *ref;
	}

	template <class Type>
	inline constexpr Type& Optional<Type&>::value() const
	{
		if (!ref)
		{
			throw BadOptionalAccess{};
		}

		return *ref;
	}

	template <class Type>
	template <class V>
	inline constexpr std::decay_t<Type> Optional<Type&>::value_or(V&& v) const
	{
		return *this ? **this : detail::convert<std::decay_t<Type>>(std::forward<V>(v));
	}

	template <class Type>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<std::decay_t<Type>, Fty>>*>
	inline constexpr std::decay_t<Type> Optional<Type&>::value_or_eval(Fty f) const
	{
		return *this ? **this : f();
	}

	template <class Type>
	inline void Optional<Type&>::reset() noexcept
	{
		ref = nullptr;
	}

	template <class Type>
	inline void Optional<Type&>::reset(Type& v) noexcept
	{
		emplace(v);
	}

	template <class Type>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>*>
	inline void Optional<Type&>::then(Fty f)
	{
		if (has_value())
		{
			f(value());
		}
	}

	template <class Type>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, const Type&>>*>
	inline void Optional<Type&>::then(Fty f) const
	{
		if (has_value())
		{
			f(value());
		}
	}

	template <class Type>
	template <class Fty, class R>
	inline Optional<R> Optional<Type&>::map(Fty f)
	{
		if (has_value())
		{
			return f(value());
		}
		else
		{
			return none;
		}
	}

	template <class Type>
	template <class Fty, class R>
	inline Optional<R> Optional<Type&>::map(Fty f) const
	{
		if (has_value())
		{
			return f(value());
		}
		else
		{
			return none;
		}
	}


	template <class Type>
	inline constexpr bool operator ==(const Optional<Type>& x, const Optional<Type>& y)
	{
		return static_cast<bool>(x) != static_cast<bool>(y) ? false : static_cast<bool>(x) == false ? true : *x == *y;
	}

	template <class Type>
	inline constexpr bool operator !=(const Optional<Type>& x, const Optional<Type>& y)
	{
		return !(x == y);
	}

	template <class Type>
	inline constexpr bool operator <(const Optional<Type>& x, const Optional<Type>& y)
	{
		return (!y) ? false : (!x) ? true : *x < *y;
	}

	template <class Type>
	inline constexpr bool operator >(const Optional<Type>& x, const Optional<Type>& y)
	{
		return (y < x);
	}

	template <class Type>
	inline constexpr bool operator <=(const Optional<Type>& x, const Optional<Type>& y)
	{
		return !(y < x);
	}

	template <class Type>
	inline constexpr bool operator >=(const Optional<Type>& x, const Optional<Type>& y)
	{
		return !(x < y);
	}

	template <class Type>
	inline constexpr bool operator ==(const Optional<Type>& x, None_t) noexcept
	{
		return (!x);
	}

	template <class Type>
	inline constexpr bool operator ==(None_t, const Optional<Type>& x) noexcept
	{
		return (!x);
	}

	template <class Type>
	inline constexpr bool operator !=(const Optional<Type>& x, None_t) noexcept
	{
		return static_cast<bool>(x);
	}

	template <class Type>
	inline constexpr bool operator !=(None_t, const Optional<Type>& x) noexcept
	{
		return static_cast<bool>(x);
	}

	template <class Type>
	inline constexpr bool operator <(const Optional<Type>&, None_t) noexcept
	{
		return false;
	}

	template <class Type>
	inline constexpr bool operator <(None_t, const Optional<Type>& x) noexcept
	{
		return static_cast<bool>(x);
	}

	template <class Type>
	inline constexpr bool operator <=(const Optional<Type>& x, None_t) noexcept
	{
		return (!x);
	}

	template <class Type>
	inline constexpr bool operator <=(None_t, const Optional<Type>&) noexcept
	{
		return true;
	}

	template <class Type>
	inline constexpr bool operator >(const Optional<Type>& x, None_t) noexcept
	{
		return static_cast<bool>(x);
	}

	template <class Type>
	inline constexpr bool operator >(None_t, const Optional<Type>&) noexcept
	{
		return false;
	}

	template <class Type>
	inline constexpr bool operator >=(const Optional<Type>&, None_t) noexcept
	{
		return true;
	}

	template <class Type>
	inline constexpr bool operator >=(None_t, const Optional<Type>& x) noexcept
	{
		return (!x);
	}

	template <class Type>
	inline constexpr bool operator ==(const Optional<Type>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x == v : false;
	}

	template <class Type>
	inline constexpr bool operator ==(const Type& v, const Optional<Type>& x)
	{
		return static_cast<bool>(x) ? v == *x : false;
	}

	template <class Type>
	inline constexpr bool operator !=(const Optional<Type>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x != v : true;
	}

	template <class Type>
	inline constexpr bool operator !=(const Type& v, const Optional<Type>& x)
	{
		return static_cast<bool>(x) ? v != *x : true;
	}

	template <class Type>
	inline constexpr bool operator <(const Optional<Type>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x < v : true;
	}

	template <class Type>
	inline constexpr bool operator >(const Type& v, const Optional<Type>& x)
	{
		return static_cast<bool>(x) ? v > * x : true;
	}

	template <class Type>
	inline constexpr bool operator >(const Optional<Type>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x > v : false;
	}

	template <class Type>
	inline constexpr bool operator <(const Type& v, const Optional<Type>& x)
	{
		return static_cast<bool>(x) ? v < *x : false;
	}

	template <class Type>
	inline constexpr bool operator >=(const Optional<Type>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x >= v : false;
	}

	template <class Type>
	inline constexpr bool operator <=(const Type& v, const Optional<Type>& x)
	{
		return static_cast<bool>(x) ? v <= *x : false;
	}

	template <class Type>
	inline constexpr bool operator <=(const Optional<Type>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x <= v : true;
	}

	template <class Type>
	inline constexpr bool operator >=(const Type& v, const Optional<Type>& x)
	{
		return static_cast<bool>(x) ? v >= *x : true;
	}

	template <class Type>
	inline constexpr bool operator ==(const Optional<Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x == v : false;
	}

	template <class Type>
	inline constexpr bool operator ==(const Type& v, const Optional<Type&>& x)
	{
		return static_cast<bool>(x) ? v == *x : false;
	}

	template <class Type>
	inline constexpr bool operator !=(const Optional<Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x != v : true;
	}

	template <class Type>
	inline constexpr bool operator !=(const Type& v, const Optional<Type&>& x)
	{
		return static_cast<bool>(x) ? v != *x : true;
	}

	template <class Type>
	inline constexpr bool operator <(const Optional<Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x < v : true;
	}

	template <class Type>
	inline constexpr bool operator >(const Type& v, const Optional<Type&>& x)
	{
		return static_cast<bool>(x) ? v > * x : true;
	}

	template <class Type>
	inline constexpr bool operator >(const Optional<Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x > v : false;
	}

	template <class Type>
	inline constexpr bool operator <(const Type& v, const Optional<Type&>& x)
	{
		return static_cast<bool>(x) ? v < *x : false;
	}

	template <class Type>
	inline constexpr bool operator >=(const Optional<Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x >= v : false;
	}

	template <class Type>
	inline constexpr bool operator <=(const Type& v, const Optional<Type&>& x)
	{
		return static_cast<bool>(x) ? v <= *x : false;
	}

	template <class Type>
	inline constexpr bool operator <=(const Optional<Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x <= v : true;
	}

	template <class Type>
	inline constexpr bool operator >=(const Type& v, const Optional<Type&>& x)
	{
		return static_cast<bool>(x) ? v >= *x : true;
	}

	template <class Type>
	inline constexpr bool operator ==(const Optional<const Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x == v : false;
	}

	template <class Type>
	inline constexpr bool operator ==(const Type& v, const Optional<const Type&>& x)
	{
		return static_cast<bool>(x) ? v == *x : false;
	}

	template <class Type>
	inline constexpr bool operator !=(const Optional<const Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x != v : true;
	}

	template <class Type>
	inline constexpr bool operator !=(const Type& v, const Optional<const Type&>& x)
	{
		return static_cast<bool>(x) ? v != *x : true;
	}

	template <class Type>
	inline constexpr bool operator <(const Optional<const Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x < v : true;
	}

	template <class Type>
	inline constexpr bool operator >(const Type& v, const Optional<const Type&>& x)
	{
		return static_cast<bool>(x) ? v > * x : true;
	}

	template <class Type>
	inline constexpr bool operator >(const Optional<const Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x > v : false;
	}

	template <class Type>
	inline constexpr bool operator <(const Type& v, const Optional<const Type&>& x)
	{
		return static_cast<bool>(x) ? v < *x : false;
	}

	template <class Type>
	inline constexpr bool operator >=(const Optional<const Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x >= v : false;
	}

	template <class Type>
	inline constexpr bool operator <=(const Type& v, const Optional<const Type&>& x)
	{
		return static_cast<bool>(x) ? v <= *x : false;
	}

	template <class Type>
	inline constexpr bool operator <=(const Optional<const Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x <= v : true;
	}

	template <class Type>
	inline constexpr bool operator >=(const Type& v, const Optional<const Type&>& x)
	{
		return static_cast<bool>(x) ? v >= *x : true;
	}


	template <class Type>
	inline constexpr Optional<std::decay_t<Type>> MakeOptional(Type&& v)
	{
		return Optional<std::decay_t<Type>>{ std::forward<Type>(v) };
	}

	template <class Type, class... Args>
	inline constexpr Optional<Type> MakeOptional(Args&&... args)
	{
		return Optional<Type>{ InPlace, std::forward<Args>(args)... };
	}

	template <class U>
	inline constexpr Optional<U&> MakeOptional(std::reference_wrapper<U> v)
	{
		return Optional<U&>{ v.get() };
	}

	template <class Type>
	inline void swap(Optional<Type>& a, Optional<Type>& b) noexcept(noexcept(a.swap(b)))
	{
		a.swap(b);
	}
}
