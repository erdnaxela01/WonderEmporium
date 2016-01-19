#ifndef __COLLISION_HANDLING_H
#define __COLLISION_HANDLING_H

#include "Core\SystemCallback.h"
#include "Scene\Scene.h"
#include "Movement\PhysicsComponent.h"
#include "CollisionHandler.h"

namespace WE
{
    //is the system that handles all the collisions and tells the objects about them
    //this system will tell all collision handling objects of a collision
    class CollisionHandling
    {
    public:
        CollisionHandling();

        virtual ~CollisionHandling();

        //static function that will get called by bullet
        static bool Collide(btManifoldPoint& manifold, void* obj1, void* obj2);

        //returns nothing
        std::vector<SystemCallback*> GetCallbacks();

        //refreshes the components the system handles
        void NotifyActiveScene(Scene* scene);


    private:
        //handles the collision between two objects
        void HandleCollision(void* obj1, void* obj2);
        ArrayList<std::pair<Entity*, CollisionHandler*>> m_Handlers;
        ArrayList<PhysicsComponent*> m_PhysicsComponents;
    };
}

#endif //__COLLISION_HANDLING_H