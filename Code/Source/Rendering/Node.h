#ifndef __NODE_H
#define __NODE_H

#include "RenderState.h"
#include "RenderComponent.h"
#include "Movement\TransformComponent.h"
#include "Core\Entity.h"

namespace WE
{
	//interface class used for nodes of a scene graph
	class Node
	{
	public:
		//set my component and transform
		Node(Entity* ent);

		//structors
		virtual ~Node() {};

		//this will render the node
		virtual void Render(RenderState* state);

        //find an entity in the scene graph
        virtual bool Find(std::string name, Entity*& entity);

	protected:
        Entity* m_Owner;
		RenderComponent* m_MyRender;
		TransformComponent* m_MyTransform;
	};
}

#endif //__NODE_H