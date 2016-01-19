#include "Timer.h"

namespace WE
{
	using Clock = std::chrono::steady_clock;
	using Duration = std::chrono::duration < double > ;

	Timer::Timer()
	{
		m_StartTime = Clock::now();
	}

	double Timer::GetSystemTime()
	{
		return std::chrono::duration_cast<Duration>(Clock::now() - m_StartTime).count();
	}

	void Timer::SetInterval(double interval)
	{
		m_IntervalTime = interval;
	}

	/*
		*Arguments:	none
		*Return: Bool
		*Purpose: tells if an interval has been passed
		START FUNCTION PassedInterval
			CALL GetSystemTime
			IF return MINUS previousTime is OVER intervalTime
				SET previousTime to return value
				RETURN true
			END IF
			RETURN false

		END FUNCTION PassedInterval
	*/
	bool Timer::PassedInterval()
	{
		double time = GetSystemTime();
		if (time - m_PreviousTime > m_IntervalTime)
		{
			m_PreviousTime = time;
			return true;
		}
		return false;
	}

	double Timer::GetInterval()
	{
		return m_IntervalTime;
	}
}