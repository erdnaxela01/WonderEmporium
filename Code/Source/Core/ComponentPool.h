#ifndef __COMPONENT_POOL_H
#define __COMPONENT_POOL_H

#include "../Tools/ArrayList.h"
#include <tuple>

namespace WE
{
    //this class will hold all the components
    template<typename... type>
    class ComponentPool
    {
    public:
        //this will return the array of the speicifc type
        template<unsigned int count, typename type>
        ArrayList<type>& Get();
    private:
        //the tupple
        std::tuple<ArrayList<type>...> m_Tupple;
    };


    template<typename... types>
    template<unsigned int count, typename type>
    ArrayList<type>& ComponentPool<types...>::Get()
    {
        return std::get<count>(m_Tupple);
    }

    
}

#endif //__COMPONENT_POOL_H