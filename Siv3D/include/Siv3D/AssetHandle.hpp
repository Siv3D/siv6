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
# include "Common.hpp"
# include "AssetIDWrapper.hpp"

namespace s3d
{
	template <class AssetType>
	struct AssetHandle
	{
	protected:

		using AssetIDWrapperType = AssetIDWrapper<AssetHandle>;

		std::shared_ptr<AssetIDWrapperType> m_handle;

	public:

		using IDType = typename AssetIDWrapperType::IDType;

		AssetHandle();

		explicit AssetHandle(std::shared_ptr<AssetIDWrapperType>&& id);

		[[nodiscard]]
		IDType id() const noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool operator ==(const AssetHandle& other) const;

		[[nodiscard]]
		bool operator !=(const AssetHandle& other) const;

		void release();
	};
}

# include "detail/AssetHandle.ipp"
