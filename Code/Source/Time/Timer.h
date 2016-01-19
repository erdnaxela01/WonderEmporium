#ifndef __TIMER_H
#define __TIMER_H

#include <chrono>

namespace WE
{
    //this will keep track of real time in order to use the time
	class Timer
	{
	public:
		using Time = std::chrono::time_point < std::chrono::system_clock > ;
		Timer();

		//get the time since the start of the timer
		double GetSystemTime();

		//set the interval time
		void SetInterval(double);

		//get the interval time
		double GetInterval();

		//check if the interval time has been passed
		bool PassedInterval();
	private:
		Time m_StartTime;
		double m_IntervalTime;
		double m_PreviousTime;

	};

}


#endif //__TIMER_H