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
		float _11, _12;
		float _21, _22;
		float _31, _32;

		Mat3x2() = default;

		constexpr Mat3x2(float _11, float _12, float _21, float _22, float _31, float _32) noexcept
			: _11{ _11 }
			, _12{ _12 }
			, _21{ _21 }
			, _22{ _22 }
			, _31{ _31 }
			, _32{ _32 } {}

		[[nodiscard]] static constexpr Mat3x2 Identity() noexcept
		{
			return Mat3x2(1.0f, 0.0f,
				0.0f, 1.0f,
				0.0f, 0.0f);
		}

		[[nodiscard]] static constexpr Mat3x2 Translate(const Float2& v) noexcept
		{
			return Mat3x2(1.0f, 0.0f,
				0.0f, 1.0f,
				v.x, v.y);
		}

		[[nodiscard]] static constexpr Mat3x2 Translate(double x, double y) noexcept
		{
			return Translate({ x, y });
		}

		[[nodiscard]] static constexpr Mat3x2 Scale(const Float2& scale, const Float2& center = Float2(0, 0)) noexcept
		{
			return Mat3x2(scale.x, 0.0f,
				0.0f, scale.y,
				center.x - scale.x * center.x, center.y - scale.y * center.y);
		}

		[[nodiscard]] static constexpr Mat3x2 Scale(double s, const Float2& center = Float2(0, 0)) noexcept
		{
			return Scale({ s, s }, center);
		}

		[[nodiscard]] static constexpr Mat3x2 Scale(double sx, double sy, const Float2& center = Float2(0, 0)) noexcept
		{
			return Scale({ sx, sy }, center);
		}

		[[nodiscard]] static Mat3x2 Rotate(double angle, const Float2& center = Float2(0, 0)) noexcept;

		[[nodiscard]] static constexpr Mat3x2 ShearX(double sx) noexcept
		{
			return Mat3x2(1.0f, 0.0f,
				-static_cast<float>(sx), 1.0f,
				0.0f, 0.0f);
		}

		[[nodiscard]] static constexpr Mat3x2 ShearY(double sy) noexcept
		{
			return Mat3x2(1.0f, static_cast<float>(sy),
				0.0f, 1.0f,
				0.0f, 0.0f);
		}

		[[nodiscard]] static constexpr Mat3x2 Screen(double width, double height) noexcept
		{
			return Screen({ width, height });
		}

		[[nodiscard]] static constexpr Mat3x2 Screen(const Float2& size) noexcept
		{
			return Mat3x2(2.0f / size.x, 0.0f,
				0.0f, -2.0f / size.y,
				-1.0f, 1.0f);
		}

		[[nodiscard]] constexpr bool operator ==(const Mat3x2& m) const noexcept
		{
			return (_11 == m._11) && (_12 == m._12)
				&& (_21 == m._21) && (_22 == m._22)
				&& (_31 == m._31) && (_32 == m._32);
		}

		[[nodiscard]] constexpr bool operator !=(const Mat3x2& m) const noexcept
		{
			return (_11 != m._11) || (_12 != m._12)
				|| (_21 != m._21) || (_22 != m._22)
				|| (_31 != m._31) || (_32 != m._32);
		}

		[[nodiscard]] Mat3x2 translated(const Float2& v) const noexcept;

		[[nodiscard]] Mat3x2 translated(double x, double y) const noexcept;

		[[nodiscard]] Mat3x2 scaled(double s, const Float2& center = Float2(0, 0)) const noexcept;

		[[nodiscard]] Mat3x2 scaled(const Float2& scale, const Float2& center = Float2(0, 0)) const noexcept;

		[[nodiscard]] Mat3x2 scaled(double sx, double sy, const Float2& center = Float2(0, 0)) const noexcept;

		[[nodiscard]] Mat3x2 rotated(double angle, const Float2& center = Float2(0, 0)) const noexcept;

		[[nodiscard]] Mat3x2 shearedX(double sx) const noexcept;

		[[nodiscard]] Mat3x2 shearedY(double sy) const noexcept;

		[[nodiscard]] constexpr float determinant() const noexcept
		{
			return (_11 * _22) - (_12 * _21);
		}

		[[nodiscard]] Mat3x2 inversed() const noexcept;

		constexpr void setProduct(const Mat3x2& a, const Mat3x2& b) noexcept
		{
			_11 = a._11 * b._11 + a._12 * b._21;
			_12 = a._11 * b._12 + a._12 * b._22;
			_21 = a._21 * b._11 + a._22 * b._21;
			_22 = a._21 * b._12 + a._22 * b._22;
			_31 = a._31 * b._11 + a._32 * b._21 + b._31;
			_32 = a._31 * b._12 + a._32 * b._22 + b._32;
		}

		[[nodiscard]] Mat3x2 operator *(const Mat3x2& matrix) const noexcept
		{
			Mat3x2 result;
			result.setProduct(*this, matrix);
			return result;
		}

		[[nodiscard]] constexpr Float2 transform(const Point& pos) const noexcept
		{
			return
			{
				pos.x * _11 + pos.y * _21 + _31,
				pos.x * _12 + pos.y * _22 + _32
			};
		}

		[[nodiscard]] constexpr Float2 transform(const Float2& pos) const noexcept
		{
			return
			{
				pos.x * _11 + pos.y * _21 + _31,
				pos.x * _12 + pos.y * _22 + _32
			};
		}

		[[nodiscard]] constexpr Vec2 transform(const Vec2& pos) const noexcept
		{
			return
			{
				pos.x * _11 + pos.y * _21 + _31,
				pos.x * _12 + pos.y * _22 + _32
			};
		}
	};
}
