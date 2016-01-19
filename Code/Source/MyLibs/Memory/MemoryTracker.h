#ifndef __MEMORY_TRACKER_H
#define __MEMORY_TRACKER_H

#ifdef MY_DEBUG

#include <vector>
#include <sstream>

namespace Memory
{
	//this class will track memory usage for the engine
	//if the memory is allocated using New and SafeDelete it will keep track of the memory allocated
	class MemoryTracker final
	{
	public:
		//structors
		MemoryTracker();
		~MemoryTracker();
		//add an adress and its info to the vector
		void AddAddress(void* v, std::string data);
		//remove an address from the vector
		void RemoveAddress(void* v);
	private:
		std::vector<std::pair<void*, std::string>> m_Addresses;
	};

	//this global is defined in the cpp
	extern MemoryTracker g_Tracker;
}

struct NewHolder 
{
	//this will pass the data for the value
	NewHolder(std::string file , long line)
	{
		//setting the values for the data
		std::stringstream ss;
		ss << file << " Line:" << line;
		data = ss.str();
	}
	std::string data;
};

template<typename rhs>
rhs* operator==(NewHolder h, rhs* r)
{
	Memory::g_Tracker.AddAddress(r, h.data);
	return r;
}


//used as tag
struct DeleteHolder 
{
    DeleteHolder(bool del = false) :deleteArray(del) {};
    bool deleteArray;
};

template<typename rhs>
void operator==(DeleteHolder h, rhs* r)
{
	Memory::g_Tracker.RemoveAddress(r);
    if (!h.deleteArray)
    {
        delete r;
    }
    else
    {
        delete[] r;
    }
}

#define New NewHolder(__FILE__, __LINE__) == new

#define SafeDelete(a) do{if(a != nullptr) {DeleteHolder() == a; a = nullptr;}}while(0)

#define SafeDeleteArray(a) do{if(a != nullptr) {DeleteHolder(true) == a; a = nullptr;}}while(0)

#else

#define New new

#define  SafeDelete(a) do{if(a != nullptr) {delete a; a = nullptr;}}while(0)

#define SafeDeleteArray(a)  do{if(a != nullptr) {delete[] a; a = nullptr;}}while(0)

#endif


#endif //__MEMORY_TRACKER_H