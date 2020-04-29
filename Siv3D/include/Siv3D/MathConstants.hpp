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
# include <limits>
# include <numbers>

# ifdef __cpp_lib_concepts
#	define SIV3D_MATH_CONSTANTS_CONCEPT template <Concept::FloatingPoint FloatingPoint>
# else
#	define SIV3D_MATH_CONSTANTS_CONCEPT template <class FloatingPoint>
# endif

namespace s3d
{
	namespace Math
	{
		inline namespace Constants
		{
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint E_v			= FloatingPoint(2.718281828459045235360287471352662498L);

			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint Log2E_v		= FloatingPoint(1.442695040888963407359924681001892137L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint Log10E_v		= FloatingPoint(0.434294481903251827651128918916605082L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint Pi_v			= FloatingPoint(3.141592653589793238462643383279502884L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint QuarterPi_v	= FloatingPoint(0.785398163397448309615660845819875721L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint OneThirdPi_v	= FloatingPoint(1.047197551196597746154214461093167628L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint HalfPi_v		= FloatingPoint(1.570796326794896619231321691639751442L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint TwoPi_v		= FloatingPoint(6.283185307179586476925286766559005768L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint InvTwoPi_v	= FloatingPoint(0.159154943091895335768883763372514362L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint InvPi_v		= FloatingPoint(0.318309886183790671537767526745028724L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint InvSqrtPi_v	= FloatingPoint(0.564189583547756286948079451560772586L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint Ln2_v		= FloatingPoint(0.693147180559945309417232121458176568L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint Ln10_v		= FloatingPoint(2.302585092994045684017991454684364208L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint Sqrt2_v		= FloatingPoint(1.414213562373095048801688724209698078L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint Sqrt3_v		= FloatingPoint(1.732050807568877293527446341505872366L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint InvSqrt2_v	= FloatingPoint(0.707106781186547524400844362104849039L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint InvSqrt3_v	= FloatingPoint(0.577350269189625764509148780501957456L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint EGamma_v		= FloatingPoint(0.577215664901532860606512090082402431L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint Phi_v		= FloatingPoint(1.618033988749894848204586834365638117L);
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint QNaN_v		= std::numeric_limits<FloatingPoint>::quiet_NaN();
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint NaN_v		= std::numeric_limits<FloatingPoint>::signaling_NaN();
			
			SIV3D_MATH_CONSTANTS_CONCEPT
			inline constexpr FloatingPoint Inf_v		= std::numeric_limits<FloatingPoint>::infinity();

			/// <summary>
			/// (float) π
			/// </summary>
			inline constexpr float PiF			= Pi_v<float>;

			/// <summary>
			/// (float) π/4
			/// </summary>
			inline constexpr float QuarterPiF	= QuarterPi_v<float>;

			/// <summary>
			/// (float) π/3
			/// </summary>
			inline constexpr float OneThirdPiF	= OneThirdPi_v<float>;

			/// <summary>
			/// (float) π/2
			/// </summary>
			inline constexpr float HalfPiF		= HalfPi_v<float>;

			/// <summary>
			/// (float) 2 * π
			/// </summary>
			inline constexpr float TwoPiF		= TwoPi_v<float>;


			/// <summary>
			/// 自然対数の底
			/// Euler's number
			/// </summary>
			inline constexpr double E			= E_v<double>;

			/// <summary>
			/// 2 を底とする e の対数
			/// </summary>
			inline constexpr double Log2E		= Log2E_v<double>;
			
			/// <summary>
			/// 10 を底とする e の対数
			/// </summary>
			inline constexpr double Log10E		= Log10E_v<double>;

			/// <summary>
			/// π
			/// </summary>
			inline constexpr double Pi			= Pi_v<double>;

			/// <summary>
			/// π/4
			/// </summary>
			inline constexpr double QuarterPi	= QuarterPi_v<double>;

			/// <summary>
			/// π/3
			/// </summary>
			inline constexpr double OneThirdPi	= OneThirdPi_v<double>;

			/// <summary>
			/// π/2
			/// </summary>
			inline constexpr double HalfPi		= HalfPi_v<double>;

			/// <summary>
			/// 2 * π
			/// </summary>
			inline constexpr double TwoPi		= TwoPi_v<double>;

			/// <summary>
			/// 1 / (2π)
			/// </summary>
			inline constexpr double InvTwoPi	= InvTwoPi_v<double>;

			/// <summary>
			/// 1 / π
			/// </summary>
			inline constexpr double InvPi		= InvPi_v<double>;
	
			/// <summary>
			/// 1 / √π
			/// </summary>
			inline constexpr double InvSqrtPi	= InvSqrtPi_v<double>;

			/// <summary>
			/// 2 の自然対数
			/// </summary>
			inline constexpr double Ln2			= Ln2_v<double>;

			/// <summary>
			/// 10 の自然対数
			/// </summary>
			inline constexpr double Ln10		= Ln10_v<double>;

			/// <summary>
			/// √2
			/// </summary>			
			inline constexpr double Sqrt2		= Sqrt2_v<double>;

			/// <summary>
			/// √3
			/// </summary>		
			inline constexpr double Sqrt3		= Sqrt3_v<double>;

			/// <summary>
			/// 1 / √2
			/// </summary>		
			inline constexpr double InvSqrt2	= InvSqrt2_v<double>;

			/// <summary>
			/// 1 / √3
			/// </summary>		
			inline constexpr double InvSqrt3	= InvSqrt3_v<double>;

			/// <summary>
			/// オイラーの定数
			/// </summary>				
			inline constexpr double EGamma		= EGamma_v<double>;

			/// <summary>
			/// 黄金数 (φ)
			/// Golden Ratio
			/// </summary>
			inline constexpr double Phi			= Phi_v<double>;

			/// <summary> 
			/// Quiet NaN
			/// </summary>
			inline constexpr double QNaN		= QNaN_v<double>;

			/// <summary>
			/// Signaling NaN
			/// </summary>
			inline constexpr double NaN			= NaN_v<double>;

			/// <summary>
			/// +Inf
			/// </summary>
			inline constexpr double Inf			= Inf_v<double>;
		}
	}

	inline namespace Literals
	{
		inline namespace MathLiterals
		{
			[[nodiscard]] 
			inline constexpr double operator ""_pi(long double x);

			[[nodiscard]]
			inline constexpr double operator ""_pi(unsigned long long x);

			[[nodiscard]]
			inline constexpr double operator ""_deg(long double deg);

			[[nodiscard]]
			inline constexpr double operator ""_deg(unsigned long long deg);
		}
	}
}

# include "MathConstants.ipp"
