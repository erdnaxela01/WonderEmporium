#include "CollisionHandling.h"

namespace WE
{
    static CollisionHandling* s_Collider = nullptr;

    CollisionHandling::CollisionHandling()
    {
        s_Collider = this;
        gContactProcessedCallback = &CollisionHandling::Collide;
    }

    CollisionHandling::~CollisionHandling()
    {

    }

    //static function that will get called by bullet
    bool CollisionHandling::Collide(btManifoldPoint& manifold, void* obj1, void* obj2)
    {
        s_Collider->HandleCollision(obj1, obj2);
        return true;
    }

    //returns nothing
    std::vector<SystemCallback*> CollisionHandling::GetCallbacks()
    {
        //return nothing
        return{};
    }

    //refreshes the components the system handles
    void CollisionHandling::NotifyActiveScene(Scene* scene)
    {
        //remove all our components
        for (int32 i = m_Handlers.Size() - 1; i >= 0; i--)
        {
            m_Handlers.PopBack();
        }
        for (int32 i = m_PhysicsComponents.Size() - 1; i >= 0; i--)
        {
            m_PhysicsComponents.PopBack();
        }

        ArrayList<Entity*>* entities = scene->GetEntities();

        //loop through all the entities and find the ones with a collision handler and physics component
        for (uint32 i = 0; i < entities->Size(); i++)
        {
            Entity* ent = (*entities)[i];
            if (ent->HasType<CollisionHandler>())
            {
                if (ent->HasType<PhysicsComponent>())
                {
                    m_Handlers.PushBack(std::make_pair(ent, ent->GetComponent<CollisionHandler>()));
                    m_PhysicsComponents.PushBack(ent->GetComponent<PhysicsComponent>());
                }
            }
        }
    }


    //handles the collision between two objects
    void CollisionHandling::HandleCollision(void* obj1, void* obj2)
    {
        std::pair<Entity*, CollisionHandler*> collide1 = std::make_pair(nullptr, nullptr);
		std::pair<Entity*, CollisionHandler*> collide2 = std::make_pair(nullptr, nullptr);

        //find the ones that collided
        for (uint32 i = 0; i < m_PhysicsComponents.Size(); i++)
        {
            if (m_PhysicsComponents[i]->GetBody() == obj1)
            {
                collide1 = m_Handlers[i];
            }
            else if (m_PhysicsComponents[i]->GetBody() == obj2)
            {
                collide2 = m_Handlers[i];
            }
            
        }

        //notify them of the collision
		if (collide1.first != nullptr && collide2.first != nullptr)
		{
			collide1.second->HandleCollision(collide1.first, collide2.first);
			collide2.second->HandleCollision(collide2.first, collide1.first);
		}
    }
}