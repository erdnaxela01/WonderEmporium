#ifndef __PARENT_NODE_H
#define __PARENT_NODE_H

#include "Node.h"
#include "Tools\ArrayList.h"
#include "RenderComponent.h"
#include "Movement\TransformComponent.h"
#include "Core\Entity.h"


namespace WE
{
    //this class will apply its matrices to all its children and so they will be locked to this object
	class ParentNode : public Node
	{
	public:
		//set the parent of the node
		ParentNode(Entity* entity);

		//structor
		virtual ~ParentNode() {};

		//render the node
		void Render(RenderState* state);

		//add a child
		void AddChild(Entity* e);

        //remove a child
        void RemoveChild(Entity* e);

        //finds it through the children
        bool Find(std::string name, Entity*& entity) override;

	private:
		ArrayList<Node*> m_Children;
	};
}


#endif //__PARENT_NODE_H