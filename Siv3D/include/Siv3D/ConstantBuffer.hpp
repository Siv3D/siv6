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
# include <memory>
# include "Common.hpp"
# include "Memory.hpp"

namespace s3d
{
	class IConstantBufferDetail;

	class ConstantBufferBase
	{
	private:

		std::shared_ptr<IConstantBufferDetail> pImpl;

	public:

		ConstantBufferBase() = default;

		ConstantBufferBase(const ConstantBufferBase&) = default;

		explicit ConstantBufferBase(size_t size);

		bool _internal_update(const void* data, size_t size);

		const IConstantBufferDetail* _detail() const;
	};

	template <class Type>
	class ConstantBuffer
	{
	private:

		static_assert(sizeof(Type) <= (16 * 4096)); // <= 64KB

		static constexpr size_t _alignment = Max<size_t>(alignof(Type), 16);

		struct alignas(_alignment) WrapperType
		{
			Type data;
		};

		ConstantBufferBase m_base;

		WrapperType* const m_wrapper	= AlignedNew<WrapperType>();

		bool m_hasDirty					= false;

		bool update()
		{
			return m_base._internal_update(&(m_wrapper->data), Size);
		}

	public:

		static constexpr size_t Size		= sizeof(WrapperType);

		static constexpr size_t Alignment	= alignof(WrapperType);

		ConstantBuffer()
			: m_base(Size)
		{

		}

		explicit ConstantBuffer(const Type& data)
			: ConstantBuffer()
		{
			m_hasDirty		= true;
			m_wrapper->data	= data;
		}

		~ConstantBuffer()
		{
			AlignedDelete(m_wrapper);
		}

		[[nodiscard]]
		constexpr size_t size() const noexcept
		{
			return Size;
		}

		[[nodiscard]]
		const float* data() const noexcept
		{
			return static_cast<const float*>(static_cast<const void*>(&(m_wrapper->data)));
		}

		[[nodiscard]]
		Type& get() noexcept
		{
			m_hasDirty = true;
			return *(m_wrapper->data);
		}

		[[nodiscard]]
		const Type& get() const noexcept
		{
			return *(m_wrapper->data);
		}

		bool _update_if_dirty()
		{
			if (!m_hasDirty)
			{
				return true;
			}

			return update();
		}

		[[nodiscard]]
		const ConstantBufferBase& base() const noexcept
		{
			return m_base;
		}

		[[nodiscard]]
		Type& operator *() noexcept
		{
			m_hasDirty = true;
			return *(m_wrapper->data);
		}

		[[nodiscard]]
		const Type& operator *() const noexcept
		{
			return *(m_wrapper->data);
		}

		[[nodiscard]]
		Type* operator ->() noexcept
		{
			m_hasDirty = true;
			return &(m_wrapper->data);
		}

		[[nodiscard]]
		const Type* operator ->() const noexcept
		{
			return &(m_wrapper->data);
		}
	};
}
