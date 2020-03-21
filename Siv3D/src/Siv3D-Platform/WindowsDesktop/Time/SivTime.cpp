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

# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Time.hpp>

namespace s3d
{
	namespace detail
	{
		inline double QueryPerformanceFrequency() noexcept
		{
			::LARGE_INTEGER frequency;
			::QueryPerformanceFrequency(&frequency);
			return static_cast<double>(frequency.QuadPart);
		}

		inline int64 GetPerformanceCount() noexcept
		{
			::LARGE_INTEGER counter;
			::QueryPerformanceCounter(&counter);
			return counter.QuadPart;
		}

		const double QPF_Sec		= (1 / QueryPerformanceFrequency());
		const double QPF_Millisec	= (1'000 / QueryPerformanceFrequency());
		const double QPF_Microsec	= (1'000'000 / QueryPerformanceFrequency());
		const double QPF_Nanosec	= (1'000'000'000 / QueryPerformanceFrequency());
	}

	namespace Time
	{
		uint64 GetSec() noexcept
		{
			return static_cast<uint64>(detail::GetPerformanceCount() * detail::QPF_Sec);
		}

		uint64 GetMillisec() noexcept
		{
			return static_cast<uint64>(detail::GetPerformanceCount() * detail::QPF_Millisec);
		}

		uint64 GetMicrosec() noexcept
		{
			return static_cast<uint64>(detail::GetPerformanceCount() * detail::QPF_Microsec);
		}

		uint64 GetNanosec() noexcept
		{
			return static_cast<uint64>(detail::GetPerformanceCount() * detail::QPF_Nanosec);
		}
	}
}
