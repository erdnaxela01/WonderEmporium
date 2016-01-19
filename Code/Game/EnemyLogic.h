#ifndef __ENEMY_LOGIC_H
#define __ENEMY_LOGIC_H

#include "../Source/Logic/LogicComponent.h"
#include "../Source/Movement/TransformComponent.h"

namespace Game
{
    //this is the logic that will control the enemy's brain
    //it will make the enemy move around
    class EnemyLogic : public WE::LogicComponent
    {
    public:
        EnemyLogic(WE::TransformComponent* transform);

        virtual ~EnemyLogic();

        //set the start and end of the enemy's logic
        void SetStartAndEnd(vec3f, vec3f);

        void SetTime(double time);

        //update the logic of the enemy
        void Update(double delta);
    private:
        vec3f m_StartPosition;
        vec3f m_EndPosition;
        double m_CurrentDelta;
        double m_Time;

        WE::TransformComponent* m_MyTransform;

    };
}


#endif //__ENEMY_LOGiC_H