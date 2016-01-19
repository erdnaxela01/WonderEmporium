#ifndef __RENDER_SYSTEM_H
#define __RENDER_SYSTEM_H

#include "MyLibs\OpenGL\ShaderProgram.h"
#include "Core\SystemVarying.h"

#include "SceneGraphComponent.h"
#include "CameraComponent.h"
#include "Movement\TransformComponent.h"
#include "Scene\Scene.h"
#include "MyLibs\OpenGL\DeferedRenderer.h"

#include <string>
#include <map>

namespace WE
{

    //this will render all rendercomponents that it finds in the current scene
	class RenderSystem
	{
	public:
		//create the system
		RenderSystem(Core* core);
		//destroy the system
		virtual ~RenderSystem();

		//notify the system of a new entity or a new component
		void NotifyActiveScene(Scene* scene);

		//get the systems callbacks
		std::vector<SystemCallback*> GetCallbacks();

        //return the renderer
        DeferedRenderer* GetRenderer();

        //return the window
        Window* GetWindow();

	private:
		static const unsigned int NUMBER_OF_MATRICES;

		void Render();

		Window m_Window;
		ArrayList<SceneGraphComponent*, 10> m_Scenes;

		Core* m_Core;

		UniformBuffer* m_MatrixBuffer;

        DeferedRenderer* m_Renderer;

        

	};
}
#endif //__RENDER_SYSTEM_H