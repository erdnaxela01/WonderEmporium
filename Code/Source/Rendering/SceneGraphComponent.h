#ifndef __SCENE_GRAPH_COMPONENT_H
#define __SCENE_GRAPH_COMPONENT_H

#include "RenderComponent.h"
#include "Movement\TransformComponent.h"
#include "Tools\ArrayList.h"
#include "CameraComponent.h"
#include "Node.h"
#include <string>

namespace WE
{
    //this is used for nodes into the engine that will be part of a scene graph
    //you can search for a node based on its name and you can add different kidns of nodes to the scene graph
    class SceneGraphComponent
    {
    public:
        SceneGraphComponent();

        virtual ~SceneGraphComponent() {};

        //render all the children
        void Render(RenderState* state);
        //add a child to the scene graph
        void AddChild(Entity*);

        //add a specific node if need be
        void AddChild(Node*);

		//add a camera
		void AddCamera(Entity*);

        //find the entity with the specified name
        bool Find(std::string name, Entity*& result);
        
    private:
        //all the renderables
        ArrayList<Node*> m_Renderables;
		//all the cameras
		ArrayList<std::pair<CameraComponent*, TransformComponent*>, 3> m_Cameras;
        
        
    };
}

#endif //__SCENE_GRAPH_COMPONENT_H