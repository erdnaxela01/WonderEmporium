#include "EnemyLogic.h"

using namespace WE;

namespace Game
{
    EnemyLogic::EnemyLogic(WE::TransformComponent* transform) :m_CurrentDelta(0.0),
        m_Time(0.0), m_MyTransform(transform)
    {

    }

    EnemyLogic::~EnemyLogic()
    {

    }

    //set the start and end of the enemy's logic
    void EnemyLogic::SetStartAndEnd(vec3f start, vec3f end)
    {
        m_StartPosition = start;
        m_EndPosition = end;
        m_CurrentDelta = 0.0;
    }

    //update the logic of the enemy
    void EnemyLogic::Update(double delta)
    {
        m_CurrentDelta += delta;
        //if the time is passed swap the direction and reset the time
        if (m_CurrentDelta >= m_Time)
        {
            m_CurrentDelta = 0.0;
            
        }

        //get a percentage and get the position between those two positions
        float percentage = m_CurrentDelta / m_Time;
        //sinusoidal interpolation
        vec3f pos = m_StartPosition + ((m_EndPosition - m_StartPosition) * (sin(PI * percentage)));

        m_MyTransform->SetPosition(pos);
    }

    void EnemyLogic::SetTime(double time)
    {
        m_Time = time;
    }
}