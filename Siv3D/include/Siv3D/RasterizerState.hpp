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
# include <cstring>
# include <functional>
# include "Common.hpp"
# include "Utility.hpp"

namespace s3d
{
	enum class FillMode : uint8
	{
		Wireframe = 2,
		
		Solid = 3,
	};

	enum class CullMode : uint8
	{
		None = 1,
		
		Front = 2,
		
		Back = 3,
	};

	/// <summary>
	/// ラスタライザーステート
	/// </summary>
	struct RasterizerState
	{
	private:

		enum class Predefined
		{
			SolidCullBack,
			
			SolidCullFront,
			
			SolidCullNone,
			
			WireframeCullBack,
			
			WireframeCullFront,
			
			WireframeCullNone,
			
			AntialiasedLine3D,

			SolidCullBackScissor,

			SolidCullFrontScissor,

			SolidCullNoneScissor,

			WireframeCullBackScissor,

			WireframeCullFrontScissor,

			WireframeCullNoneScissor,

			AntialiasedLine3DScissor,
			
			Default2D = SolidCullNone,
			
			Default3D = SolidCullBack,
		};

	public:

		using storage_type = uint64;

		/// @brief 面の塗りつぶし方法
		FillMode fillMode : 2	= FillMode::Solid;

		/// @brief カリングの基準
		CullMode cullMode : 2	= CullMode::Back;

		/// @brief シザーテストの有効無効
		bool scissorEnable : 2	= false;

		/// @brief アンチエイリアスされた Line3D 描画
		bool antialiasedLine3D : 2	= false;

		/// @brief 深度バイアス
		int32 depthBias	= 0;

		explicit constexpr RasterizerState(
			FillMode _fillMode = FillMode::Solid,
			CullMode _cullMode = CullMode::Back,
			bool _scissorEnable = false,
			bool _antialiasedLine3D = false,
			int32 _depthBias = 0
		)
			: fillMode(_fillMode)
			, cullMode(_cullMode)
			, scissorEnable(_scissorEnable)
			, antialiasedLine3D(_antialiasedLine3D)
			, depthBias(_depthBias) {}

		constexpr RasterizerState(Predefined predefined) noexcept;

		[[nodiscard]]
		storage_type asValue() const noexcept
		{
			storage_type t;
			std::memcpy(&t, this, sizeof(storage_type));
			return t;
		}

		[[nodiscard]]
		bool operator ==(const RasterizerState& other) const noexcept
		{
			return (asValue() == other.asValue());
		}

		[[nodiscard]]
		bool operator !=(const RasterizerState& other) const noexcept
		{
			return (asValue() != other.asValue());
		}

		/// <summary>
		/// ソリッド表示、裏向きの面をカリング
		/// RasterizerState{ FillMode::Solid, CullMode::Back }
		/// </summary>
		static const Predefined SolidCullBack = Predefined::SolidCullBack;

		/// <summary>
		/// ソリッド表示、表向きの面をカリング
		/// RasterizerState{ FillMode::Solid, CullMode::Front }
		/// </summary>
		static const Predefined SolidCullFront = Predefined::SolidCullFront;

		/// <summary>
		/// ソリッド表示、カリングなし
		/// RasterizerState{ FillMode::Solid, CullMode::None }
		/// </summary>
		static const Predefined SolidCullNone = Predefined::SolidCullNone;

		/// <summary>
		/// ワイヤフレーム表示、裏向きの面をカリング
		/// RasterizerState{ FillMode::Wireframe, CullMode::Back }
		/// </summary>
		static const Predefined WireframeCullBack = Predefined::WireframeCullBack;

		/// <summary>
		/// ワイヤフレーム表示、表向きの面をカリング
		/// RasterizerState{ FillMode::Wireframe, CullMode::Front }
		/// </summary>
		static const Predefined WireframeCullFront = Predefined::WireframeCullFront;

		/// <summary>
		/// ワイヤフレーム表示、カリングなし
		/// RasterizerState{ FillMode::Wireframe, CullMode::None }
		/// </summary>
		static const Predefined WireframeCullNone = Predefined::WireframeCullNone;

		/// <summary>
		/// アンチエイリアスされた Line3D 描画
		/// RasterizerState{ FillMode::Solid, CullMode::None, false, true }
		/// </summary>
		static const Predefined AntialiasedLine3D = Predefined::AntialiasedLine3D;

		/// <summary>
		/// ソリッド表示、裏向きの面をカリング、シザーテスト
		/// RasterizerState{ FillMode::Solid, CullMode::Back, true }
		/// </summary>
		static const Predefined SolidCullBackScissor = Predefined::SolidCullBackScissor;

		/// <summary>
		/// ソリッド表示、表向きの面をカリング、シザーテスト
		/// RasterizerState{ FillMode::Solid, CullMode::Front, true }
		/// </summary>
		static const Predefined SolidCullFrontScissor = Predefined::SolidCullFrontScissor;

		/// <summary>
		/// ソリッド表示、カリングなし、シザーテスト
		/// RasterizerState{ FillMode::Solid, CullMode::None, true }
		/// </summary>
		static const Predefined SolidCullNoneScissor = Predefined::SolidCullNoneScissor;

		/// <summary>
		/// ワイヤフレーム表示、裏向きの面をカリング、シザーテスト
		/// RasterizerState{ FillMode::Wireframe, CullMode::Back, true }
		/// </summary>
		static const Predefined WireframeCullBackScissor = Predefined::WireframeCullBackScissor;

		/// <summary>
		/// ワイヤフレーム表示、表向きの面をカリング、シザーテスト
		/// RasterizerState{ FillMode::Wireframe, CullMode::Front, true }
		/// </summary>
		static const Predefined WireframeCullFrontScissor = Predefined::WireframeCullFrontScissor;

		/// <summary>
		/// ワイヤフレーム表示、カリングなし、シザーテスト
		/// RasterizerState{ FillMode::Wireframe, CullMode::None, true }
		/// </summary>
		static const Predefined WireframeCullNoneScissor = Predefined::WireframeCullNoneScissor;
		
		/// <summary>
		/// アンチエイリアスされた Line3D 描画、シザーテスト
		/// RasterizerState{ FillMode::Solid, CullMode::None, true, true }
		/// </summary>
		static const Predefined AntialiasedLine3DScissor = Predefined::AntialiasedLine3DScissor;

		/// <summary>
		/// 2D 描画時のデフォルト
		/// RasterizerState::SolidNone
		/// </summary>
		static const Predefined Default2D = Predefined::Default2D;

		/// <summary>
		/// 3D 描画時のデフォルト
		/// RasterizerState::SolidBack
		/// </summary>
		static const Predefined Default3D = Predefined::Default3D;
	};
	static_assert(sizeof(RasterizerState) == sizeof(RasterizerState::storage_type));

	inline constexpr RasterizerState::RasterizerState(const Predefined predefined) noexcept
	{
		constexpr RasterizerState PredefinedStates[14] =
		{
			RasterizerState{ FillMode::Solid,		CullMode::Back },	// SolidCullBack
			RasterizerState{ FillMode::Solid,		CullMode::Front },	// SolidCullFront
			RasterizerState{ FillMode::Solid,		CullMode::None },	// SolidCullNone
			RasterizerState{ FillMode::Wireframe,	CullMode::Back },	// WireframeCullBack
			RasterizerState{ FillMode::Wireframe,	CullMode::Front },	// WireframeCullFront
			RasterizerState{ FillMode::Wireframe,	CullMode::None },	// WireframeCullNone
			RasterizerState{ FillMode::Solid,		CullMode::None, false, true },	// AntialiasedLine3D
			RasterizerState{ FillMode::Solid,		CullMode::Back, true },			// SolidCullBackScissor
			RasterizerState{ FillMode::Solid,		CullMode::Front, true },		// SolidCullFrontScissor
			RasterizerState{ FillMode::Solid,		CullMode::None, true },			// SolidCullNoneScissor
			RasterizerState{ FillMode::Wireframe,	CullMode::Back, true },			// WireframeCullBackScissor
			RasterizerState{ FillMode::Wireframe,	CullMode::Front, true },		// WireframeCullFrontScissor
			RasterizerState{ FillMode::Wireframe,	CullMode::None, true },			// WireframeCullNoneScissor
			RasterizerState{ FillMode::Solid,		CullMode::None, true, true },	// AntialiasedLine3DScissor
		};

		*this = PredefinedStates[FromEnum(predefined)];
	}
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::RasterizerState>
{
	[[nodiscard]]
	size_t operator()(const s3d::RasterizerState& value) const noexcept
	{
		return hash<s3d::RasterizerState::storage_type>()(value.asValue());
	}
};
