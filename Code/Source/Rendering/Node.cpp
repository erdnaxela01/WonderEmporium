#include "Node.h"
#include "Core\Entity.h"
#include <cassert>

namespace WE
{

	
	Node::Node(Entity* ent)
	{
		//make sure the entity has a transform and a rendercomponent
		assert(ent->HasType<TransformComponent>() && ent->HasType<RenderComponent>());

		m_MyRender = ent->GetComponent<RenderComponent>();
		m_MyTransform = ent->GetComponent<TransformComponent>();
        m_Owner = ent;
	}


	void Node::Render(RenderState* state)
	{

		//add our matrix
		state->stack->Multiply(m_MyTransform->GetTransform());
        state->normalStack->Multiply(m_MyTransform->GetInverse());
		//render the component
		m_MyRender->Render(state);

		//pop our matrix
		state->stack->Pop();
        state->normalStack->Pop();
	}

    bool Node::Find(std::string name, Entity*& entity)
    {
        if (m_Owner->Name() == name)
        {
            entity = m_Owner;
            return true;
        }
        return false;
    }
}