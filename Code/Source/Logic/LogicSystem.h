#ifndef __LOGIC_SYSTEM_H
#define __LOGIC_SYSTEM_H

#include "Time\Timer.h"
#include "LogicComponent.h"


#include "Core\SystemCallback.h"
#include "Scene\Scene.h"

namespace WE
{
    //this logic system will update all the logic components and pass them the time
    class LogicSystem
    {
    public:
        LogicSystem();

        virtual ~LogicSystem();

        //return the update logic 
        std::vector<SystemCallback*> GetCallbacks();

        //tell the system about a new scene
        void NotifyActiveScene(Scene* scene);

    private:
        //update the logic components
        void UpdateLogic();

        Timer m_Timer;
        ArrayList<LogicComponent*> m_Logic;
    };

}


#endif //__LOGIC_SYSTEM_H