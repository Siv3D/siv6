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
	template <class Type, size_t Alignment>
	inline Type* AlignedMalloc(const size_t n)
	{
		return static_cast<Type*>(detail::AlignedMalloc<Alignment>(sizeof(Type) * n));
	}

	inline void AlignedFree(void* const p)
	{
		detail::AlignedFree(p);
	}

	template <class Type, class ...Args, std::enable_if_t<std::is_constructible_v<Type, Args...>>*>
	inline Type* AlignedNew(Args&&... args)
	{
		Type* p = AlignedMalloc<Type>();

		if (p == nullptr)
		{
			throw std::bad_alloc();
		}

		::new (p) Type(std::forward<Args>(args)...);

		return p;
	}

	template <class Type>
	inline void AlignedDelete(Type* const p)
	{
		if (p == nullptr)
		{
			return;
		}

		p->~Type();

		AlignedFree(p);
	}

	inline bool IsAligned(const void* const p, const size_t alignment) noexcept
	{
		return ((reinterpret_cast<std::uintptr_t>(p) % alignment) == 0);
	}

	template <class Type, class ...Args, std::enable_if_t<std::is_constructible_v<Type, Args...>>*>
	inline auto MakeUnique(Args&&... args)
	{
		if constexpr (IsOverAligned_v<Type>)
		{
			return std::unique_ptr<Type, AlignedDeleter<Type>>(AlignedNew<Type>(std::forward<Args>(args)...));
		}
		else
		{
			return std::make_unique<Type>(std::forward<Args>(args)...);
		}
	}

	template <class Type, class ...Args, std::enable_if_t<std::is_constructible_v<Type, Args...>>*>
	inline auto MakeShared(Args&&... args);
}
