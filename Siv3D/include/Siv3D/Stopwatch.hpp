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
# include "Duration.hpp"

namespace s3d
{
	class Stopwatch
	{
	private:

		int64 m_startTimeMicrosec = 0;

		int64 m_accumulationMicrosec = 0;

		bool m_isStarted = false;

		bool m_pausing = true;

		ISteadyClock* m_pSteadyClock = nullptr;

	public:

		explicit Stopwatch(bool startImmediately = false, ISteadyClock* pSteadyClock = nullptr);

		explicit Stopwatch(const Duration& startTime, bool startImmediately = false, ISteadyClock* pSteadyClock = nullptr);

		[[nodiscard]]
		bool isStarted() const;

		[[nodiscard]]
		bool isPaused() const;

		[[nodiscard]]
		bool isRunning() const;

		void start();

		void pause();

		void resume();

		void reset() noexcept;

		void restart();

		void set(const Duration& time);

		[[nodiscard]]
		int32 d() const;

		[[nodiscard]]
		int64 d64() const;

		[[nodiscard]]
		double dF() const;

		[[nodiscard]]
		int32 h() const;

		[[nodiscard]]
		int64 h64() const;

		[[nodiscard]]
		double hF() const;

		[[nodiscard]]
		int32 min() const;

		[[nodiscard]]
		int64 min64() const;

		[[nodiscard]]
		double minF() const;

		[[nodiscard]]
		int32 s() const;

		[[nodiscard]]
		int64 s64() const;

		[[nodiscard]]
		double sF() const;

		[[nodiscard]]
		int32 ms() const;

		[[nodiscard]]
		int64 ms64() const;

		[[nodiscard]]
		double msF() const;

		[[nodiscard]]
		int64 us() const;

		[[nodiscard]]
		int64 us64() const;

		[[nodiscard]]
		double usF() const;

		[[nodiscard]]
		Duration elapsed() const;

		[[nodiscard]]
		String format(StringView format = U"H:mm:ss.xx"_sv) const;

		[[nodiscard]]
		friend bool operator <(const Stopwatch& s, const MicrosecondsF& time)
		{
			return (s.elapsed() < time);
		}

		[[nodiscard]]
		friend bool operator <=(const Stopwatch& s, const MicrosecondsF& time)
		{
			return (s.elapsed() <= time);
		}

		[[nodiscard]]
		friend bool operator >(const Stopwatch& s, const MicrosecondsF& time)
		{
			return (s.elapsed() > time);
		}

		[[nodiscard]]
		friend bool operator >=(const Stopwatch& s, const MicrosecondsF& time)
		{
			return (s.elapsed() >= time);
		}

		[[nodiscard]]
		friend bool operator <(const MicrosecondsF& time, const Stopwatch& s)
		{
			return (time < s.elapsed());
		}

		[[nodiscard]]
		friend bool operator <=(const MicrosecondsF& time, const Stopwatch& s)
		{
			return (time <= s.elapsed());
		}

		[[nodiscard]]
		friend bool operator >(const MicrosecondsF& time, const Stopwatch& s)
		{
			return (time > s.elapsed());
		}

		[[nodiscard]]
		friend bool operator >=(const MicrosecondsF& time, const Stopwatch& s)
		{
			return (time >= s.elapsed());
		}

		/// @brief 
		/// @tparam CharType 
		/// @param output 
		/// @param value 
		/// @return 
		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Stopwatch& value)
		{
			return output << value.format();
		}

		/// @brief 
		/// @param formatData 
		/// @param value 
		friend void Formatter(FormatData& formatData, const Stopwatch& value)
		{
			formatData.string.append(value.format());
		}
	};
}

# include "detail/Stopwatch.ipp"
