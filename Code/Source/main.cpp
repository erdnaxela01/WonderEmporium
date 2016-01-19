#include "Core\Core.h"
#include "Input\InputSystem.h"
#include "Rendering\RenderSystem.h"
#include "Movement\PhysicsSystem.h"
#include "Scene\SceneManagerSystem.h"
#include "Rendering\LightingSystem.h"
#include "Rendering\FinalPassSystem.h"
#include "Logic\LogicSystem.h"
#include "Collision\CollisionHandling.h"
#include "Rendering/UISytstem.h"
#include "../Game/Game.h"


using namespace WE;


int main()
{
	Core core;

    RenderSystem* render = New RenderSystem(&core);

    //GameLoop
    core.AddSystem(New InputSystem());
    core.AddSystem(New PhysicsSystem());
	core.AddSystem(New LogicSystem());
    core.AddSystem(render);
    core.AddSystem(New LightingSystem(render->GetRenderer()));
    core.AddSystem(New FinalPassSystem(render->GetRenderer()));
    core.AddSystem(New UISystem(render->GetWindow() ));
    //loop


	core.AddSystem(New SceneManagerSystem());
	core.AddSystem(New CollisionHandling());

	SceneManagerSystem* system = core.GetSystem<SceneManagerSystem>();

	//add the scene observers
	system->AddObserver(core.GetSystem<RenderSystem>());
	system->AddObserver(core.GetSystem<InputSystem>());
	system->AddObserver(core.GetSystem<PhysicsSystem>());
    system->AddObserver(core.GetSystem<LightingSystem>());
    system->AddObserver(core.GetSystem<LogicSystem>());
    system->AddObserver(core.GetSystem<CollisionHandling>());
    system->AddObserver(core.GetSystem<UISystem>());


    //add the game
	system->AddScene(New Game::GameScene());
	system->PushScene("Game");


    //start the game loop
	while (!core.Exiting())
	{
		core.Loop();
	}


    return 0;
}