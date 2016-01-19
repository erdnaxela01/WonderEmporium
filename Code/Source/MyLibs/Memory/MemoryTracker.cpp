#include "MemoryTracker.h"


#ifdef MY_DEBUG

namespace Memory
{
	MemoryTracker::MemoryTracker()
	{
		//track when the tracker is constructing
		printf("MemoryTracker: Constructing\n");
	}
	MemoryTracker::~MemoryTracker()
	{
		//track when the memory tracker is deconstructing
        printf("MemoryTracker: Deconstructing\n");
		//if the address vector isnt empty that means we leaked
		if (!m_Addresses.empty())
		{
			std::stringstream ss;
			ss << "Memory Leaked!!!\n";
			//loop through the addresses and post which ones have leaked and where they were allocated
			for (int i = 0; i < m_Addresses.size(); i++)
			{
				ss << "[" << m_Addresses[i].first << "] declared at " << m_Addresses[i].second << "\n";
			}
			//flush the string stream
			ss.flush();
			//log the string stream
            printf(ss.str().c_str());
			
		}
		else
		{
            printf("No registered Memory Leaks Detected");
		}
		char buffer[1];
		printf("\nPress Return To Exit");
		scanf_s("s", buffer);
	}

	void MemoryTracker::AddAddress(void* v, std::string data)
	{
		m_Addresses.push_back(std::make_pair(v, data));
	}
	void MemoryTracker::RemoveAddress(void* v)
	{
		for (int i = 0; i < m_Addresses.size(); i++)
		{
			if (m_Addresses[i].first == v)
			{
				m_Addresses.erase(m_Addresses.begin() + i);
			}
		}
	}

	MemoryTracker g_Tracker;
}
#endif //MY_DEBUG