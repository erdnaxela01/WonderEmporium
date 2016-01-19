#include "SceneGraphComponent.h"
#include "../Core/Entity.h"

namespace WE
{

    void SceneGraphComponent::Render(RenderState* state)
    {
        //loop through all the renderables
		for (int c = 0; c < m_Cameras.Size(); c++)
		{
			//set the projection matrix
			m_Cameras[c].first->View(state);

			//set the view matrix
			state->stack->Multiply(m_Cameras[c].second->GetInverse());

            state->buffer->SetUniform("u_VPMatrix", state->stack->Top().GetArray(), 16, sizeof(float));

            state->stack->Pop();
            state->stack->Pop();

			//render the objects
			for (int i = 0; i < m_Renderables.Size(); i++)
			{
				m_Renderables[i]->Render(state);
			}

		}
    }

    void SceneGraphComponent::AddChild(Entity* r)
    {
        //add a child to the scene
		//if he has a node add it
		if (r->HasType<Node>())
		{
			m_Renderables.PushBack(r->GetComponent<Node>());
		}
    }

	void SceneGraphComponent::AddCamera(Entity* e)
	{
		//if the entity has a camera and a transform, add it
		if (e->HasType<CameraComponent>() && e->HasType<TransformComponent>())
		{
			m_Cameras.PushBack(std::make_pair(e->GetComponent<CameraComponent>(), e->GetComponent<TransformComponent>()));
		}
	}

    void SceneGraphComponent::AddChild(Node* n)
    {
        //add the node
        m_Renderables.PushBack(n);
    }

    SceneGraphComponent::SceneGraphComponent()
    {
       
    }

    bool SceneGraphComponent::Find(std::string name, Entity*& result)
    {
        //loop through and find the entity
        for (uint32 i = 0; i < m_Renderables.Size(); i++)
        {
            if (m_Renderables[i]->Find(name, result))
            {
                return true;
            }
        }
        return false;
    }
    
}