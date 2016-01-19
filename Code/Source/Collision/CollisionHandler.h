#ifndef __COLLISION_HANDLER_H
#define __COLLISION_HANDLER_H

#include "Core\Entity.h"

namespace WE
{

    //handles collisions from the collisions system
    //classes must implement HandleCollision
    class CollisionHandler
    {
    public:
        virtual void HandleCollision(Entity* you, Entity* other) = 0;

    private:

    };
}


#endif //__COLLISION_HANDLER_H