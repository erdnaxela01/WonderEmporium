#include "ParentNode.h"


namespace WE
{
	ParentNode::ParentNode(Entity* entity) :Node(entity)
	{
		
	}

	void ParentNode::Render(RenderState* state)
	{
		//add our matrix to the stack
		state->stack->Multiply(m_MyTransform->GetTransform());

        state->normalStack->Multiply(m_MyTransform->GetInverse());

		//render my render component
		m_MyRender->Render(state);

		//go through all the children and draw them
        for (unsigned int i = 0; i < m_Children.Size(); i++)
		{
			//render the child node
			m_Children[i]->Render(state);
		}

		//remove the matrix
		state->stack->Pop();
        state->normalStack->Pop();
	}

	//add a child
	void ParentNode::AddChild(Entity* e)
	{
		//if the entity has a node add it to the children
		if (e->HasType<Node>())
		{
			m_Children.PushBack(e->GetComponent<Node>());
		}
	}

    void ParentNode::RemoveChild(Entity* e)
    {
        //if he doesnt have a node return
        if (!e->HasType<Node>())
        {
            return;
        }
        //cache the node
        Node* n = e->GetComponent<Node>();
        for (uint32 i = 0; i < m_Children.Size(); i++)
        {
            //if the child matches
            if (m_Children[i] == n)
            {
                //swap the current and the last and remove the last
                std::swap(m_Children[i], m_Children.Back());
                m_Children.PopBack();
            }
        }
    }

    bool ParentNode::Find(std::string name, Entity*& entity)
    {
        //do I have the entity?
        if (m_Owner->Name() == name)
        {
            entity = m_Owner;
            return true;
        }

        //loop through all the children and ask them if they have the entity
        for (uint32 i = 0; i < m_Children.Size(); i++)
        {
            if (m_Children[i]->Find(name, entity))
            {
                return true;
            }
        }

        return false;
    }
}