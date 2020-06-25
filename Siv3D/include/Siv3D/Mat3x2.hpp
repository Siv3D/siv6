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
# include "PointVector.hpp"

namespace s3d
{
	struct Mat3x2
	{
		using value_type = float;

		value_type _11, _12;
		value_type _21, _22;
		value_type _31, _32;

		SIV3D_NODISCARD_CXX20
		Mat3x2() = default;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic Arithmetic>
	# else
		template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		explicit constexpr Mat3x2(Arithmetic s) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Mat3x2(float _11, float _12, float _21, float _22, float _31, float _32) noexcept;

		[[nodiscard]]
		static constexpr Mat3x2 Identity() noexcept;

		[[nodiscard]]
		static constexpr Mat3x2 Translate(Float2 v) noexcept;

		template <class X, class Y>
		[[nodiscard]]
		static constexpr Mat3x2 Translate(X x, Y y) noexcept;

		[[nodiscard]]
		static constexpr Mat3x2 Scale(Float2 scale, Float2 center = Float2(0, 0)) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic Arithmetic>
	# else
		template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>* = nullptr>
	# endif
		[[nodiscard]]
		static constexpr Mat3x2 Scale(Arithmetic s, Float2 center = Float2(0, 0)) noexcept;

		template <class X, class Y>
		[[nodiscard]]
		static constexpr Mat3x2 Scale(X sx, Y sy, Float2 center = Float2(0, 0)) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic Arithmetic>
	# else
		template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>* = nullptr>
	# endif
		[[nodiscard]]
		static Mat3x2 Rotate(Arithmetic angle, Float2 center = Float2(0, 0)) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic Arithmetic>
	# else
		template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>* = nullptr>
	# endif
		[[nodiscard]]
		static constexpr Mat3x2 ShearX(Arithmetic sx) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Arithmetic Arithmetic>
	# else
		template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>* = nullptr>
	# endif
		[[nodiscard]]
		static constexpr Mat3x2 ShearY(Arithmetic sy) noexcept;

		template <class X, class Y>
		[[nodiscard]]
		static constexpr Mat3x2 Screen(X width, Y height) noexcept;

		[[nodiscard]]
		static constexpr Mat3x2 Screen(Float2 size) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const Mat3x2& lhs, const Mat3x2& rhs) noexcept
		{
			return (lhs._11 == rhs._11) && (lhs._12 == rhs._12)
				&& (lhs._21 == rhs._21) && (lhs._22 == rhs._22)
				&& (lhs._31 == rhs._31) && (lhs._32 == rhs._32);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Mat3x2& lhs, const Mat3x2& rhs) noexcept
		{
			return (lhs._11 != rhs._11) || (lhs._12 != rhs._12)
				|| (lhs._21 != rhs._21) || (lhs._22 != rhs._22)
				|| (lhs._31 != rhs._31) || (lhs._32 != rhs._32);
		}

		[[nodiscard]]
		Mat3x2 translated(Float2 v) const noexcept;

		template <class X, class Y>
		[[nodiscard]]
		Mat3x2 translated(X x, Y y) const noexcept;

		[[nodiscard]]
		Mat3x2 scaled(double s, Float2 center = Float2(0, 0)) const noexcept;

		[[nodiscard]]
		Mat3x2 scaled(Float2 scale, Float2 center = Float2(0, 0)) const noexcept;

		[[nodiscard]]
		Mat3x2 scaled(double sx, double sy, Float2 center = Float2(0, 0)) const noexcept;

		[[nodiscard]]
		Mat3x2 rotated(double angle, Float2 center = Float2(0, 0)) const noexcept;

		[[nodiscard]]
		Mat3x2 shearedX(double sx) const noexcept;

		[[nodiscard]]
		Mat3x2 shearedY(double sy) const noexcept;

		[[nodiscard]]
		constexpr float determinant() const noexcept
		{
			return (_11 * _22) - (_12 * _21);
		}

		[[nodiscard]]
		Mat3x2 inversed() const noexcept;

		constexpr void setProduct(const Mat3x2& a, const Mat3x2& b) noexcept
		{
			_11 = a._11 * b._11 + a._12 * b._21;
			_12 = a._11 * b._12 + a._12 * b._22;
			_21 = a._21 * b._11 + a._22 * b._21;
			_22 = a._21 * b._12 + a._22 * b._22;
			_31 = a._31 * b._11 + a._32 * b._21 + b._31;
			_32 = a._31 * b._12 + a._32 * b._22 + b._32;
		}

		[[nodiscard]]
		Mat3x2 operator *(const Mat3x2& matrix) const noexcept
		{
			Mat3x2 result;
			result.setProduct(*this, matrix);
			return result;
		}

		[[nodiscard]]
		constexpr Float2 transform(Point pos) const noexcept;

		[[nodiscard]]
		constexpr Float2 transform(Float2 pos) const noexcept;

		[[nodiscard]]
		constexpr Vec2 transform(Vec2 pos) const noexcept;
	};
}

# include "detail/Mat3x2.ipp"
