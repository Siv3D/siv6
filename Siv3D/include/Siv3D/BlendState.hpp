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
	enum class Blend : uint8
	{
		Zero			= 1,
		One				= 2,
		SrcColor		= 3,
		InvSrcColor		= 4,
		SrcAlpha		= 5,
		InvSrcAlpha		= 6,
		DestAlpha		= 7,
		InvDestAlpha	= 8,
		DestColor		= 9,
		InvDestColor	= 10,
		SrcAlphaSat		= 11,
		BlendFactor		= 14,
		InvBlendFactor	= 15,
		Src1Color		= 16,
		InvSrc1Color	= 17,
		Src1Alpha		= 18,
		InvSrc1Alpha	= 19
	};

	enum class BlendOp : uint8
	{
		Add			= 1,
		Subtract	= 2,
		RevSubtract	= 3,
		Min			= 4,
		Max			= 5
	};

	struct BlendState
	{
	private:

		enum class Predefined
		{
			NonPremultiplied,

			Premultiplied,

			Opaque,

			Additive,

			Subtractive,

			Multiplicative,

			Multiplicative2X,

			Default = NonPremultiplied,
		};

	public:

		using storage_type = uint32;


		bool enable		: 1 = true;

		bool writeR		: 1 = true;

		bool writeG		: 1 = true;

		Blend src		: 5 = Blend::SrcAlpha;

		Blend dst		: 5 = Blend::InvSrcAlpha;

		BlendOp op		: 3 = BlendOp::Add;

		bool alphaToCoverageEnable : 1 = false;

		bool writeB		: 1 = true;

		bool writeA		: 1 = true;

		Blend srcAlpha	: 5 = Blend::Zero;

		Blend dstAlpha	: 5 = Blend::One;

		BlendOp opAlpha	: 3 = BlendOp::Add;


		explicit constexpr BlendState(
			bool _enable = true,
			Blend _src = Blend::SrcAlpha,
			Blend _dst = Blend::InvSrcAlpha,
			BlendOp _op = BlendOp::Add,
			Blend _srcAlpha = Blend::Zero,
			Blend _dstAlpha = Blend::One,
			BlendOp _opAlpha = BlendOp::Add,
			bool _alphaToCoverageEnable = false,
			bool _writeR = true,
			bool _writeG = true,
			bool _writeB = true,
			bool _writeA = true
		) noexcept
		: enable(_enable)
		, writeR(_writeR)
		, writeG(_writeG)
		, src(_src)
		, dst(_dst)
		, op(_op)
		, alphaToCoverageEnable(_alphaToCoverageEnable)
		, writeB(_writeB)
		, writeA(_writeA)
		, srcAlpha(_srcAlpha)
		, dstAlpha(_dstAlpha)
		, opAlpha(_opAlpha) {}

		constexpr BlendState(Predefined predefined) noexcept;

		[[nodiscard]]
		storage_type asValue() const noexcept
		{
			storage_type t;
			std::memcpy(&t, this, sizeof(storage_type));
			return t;
		}

		[[nodiscard]]
		bool operator ==(const BlendState& other) const noexcept
		{
			return (asValue() == other.asValue());
		}

		[[nodiscard]]
		bool operator !=(const BlendState& other) const noexcept
		{
			return (asValue() != other.asValue());
		}

		/// <summary>
		/// デフォルトのブレンド
		/// BlendState{ true, Blend::SrcAlpha, Blend::InvSrcAlpha, BlendOp::Add, Blend::Zero, Blend::One, BlendOp::Add }
		/// </summary>
		static constexpr Predefined NonPremultiplied = Predefined::NonPremultiplied;

		/// <summary>
		/// 乗算済みアルファブレンド
		/// BlendState{ true, Blend::One, Blend::InvSrcAlpha, BlendOp::Add, Blend::Zero, Blend::One, BlendOp::Add }
		/// </summary>
		static constexpr Predefined Premultiplied = Predefined::Premultiplied;

		/// <summary>
		/// 不透明
		/// BlendState{ false }
		/// </summary>
		static constexpr Predefined Opaque = Predefined::Opaque;

		/// <summary>
		/// 加算ブレンド
		/// BlendState{ true, Blend::SrcAlpha, Blend::One, BlendOp::Add, Blend::Zero, Blend::One, BlendOp::Add }
		/// </summary>
		static constexpr Predefined Additive = Predefined::Additive;

		/// <summary>
		/// 減算ブレンド
		/// BlendState{ true, Blend::SrcAlpha, Blend::One, BlendOp::RevSubtract, Blend::Zero, Blend::One, BlendOp::Add }
		/// </summary>
		static constexpr Predefined Subtractive = Predefined::Subtractive;

		/// <summary>
		/// 乗算ブレンド
		/// BlendState{ true, Blend::Zero, Blend::SrcColor, BlendOp::Add, Blend::Zero, Blend::One, BlendOp::Add }
		/// </summary>
		static constexpr Predefined Multiplicative = Predefined::Multiplicative;

		/// <summary>
		/// 2X 乗算ブレンド
		/// BlendState{ true, Blend::DestColor, Blend::SrcColor, BlendOp::Add, Blend::Zero, Blend::One, BlendOp::Add }
		/// </summary>
		static constexpr Predefined Multiplicative2X = Predefined::Multiplicative2X;

		/// <summary>
		/// デフォルトのブレンド
		/// BlendState{ true }
		/// </summary>
		static constexpr Predefined Default = Predefined::Default;
	};
	static_assert(sizeof(BlendState) == sizeof(BlendState::storage_type));

	inline constexpr BlendState::BlendState(const Predefined predefined) noexcept
	{
		constexpr BlendState PredefinedStates[7] =
		{
			BlendState{ true },																// NonPremultiplied
			BlendState{ true, Blend::One },													// Premultiplied
			BlendState{ false },															// Opaque
			BlendState{ true, Blend::SrcAlpha,	Blend::One,			BlendOp::Add },			// Additive
			BlendState{ true, Blend::SrcAlpha,	Blend::One,			BlendOp::RevSubtract },	// Subtractive
			BlendState{ true, Blend::Zero,		Blend::SrcColor,	BlendOp::Add },			// Multiplicative
			BlendState{ true, Blend::DestColor,	Blend::SrcColor,	BlendOp::Add },			// Multiplicative2X
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
struct std::hash<s3d::BlendState>
{
	[[nodiscard]]
	size_t operator()(const s3d::BlendState& value) const noexcept
	{
		return hash<s3d::BlendState::storage_type>()(value.asValue());
	}
};
