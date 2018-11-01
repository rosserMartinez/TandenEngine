//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include <iostream>
#include "Engine.h"
#include "Entity/Components/MeshRenderer.h"
#include "Entity/Components/Transform.h"

void Engine::StartEngine() {

}

void Engine::RunEngine() {

    while(!exitStatus)
    {
        std::cout << "Running Loop \n";
        //Get input
        Input::GetInput();

        //Process Events
        EventSystem::ProcessEvents();

        //Update all registered physics components

        //Update all the loaded scenes
        for (const auto &scene : mLoadedScenes)
        {
            if(scene != nullptr)
                scene->Update();
        }

        //Render all registered renderer components
        RenderingSystem::Draw();

        //Wait for frame time
        Timer::WaitForFrameTime();
    }
}

void Engine::StopEngine() {
	std::cout << "Closing Engine\n";
}

Engine::Engine() {
    EventSystem::RegisterListener(this);
    auto * newScene = new Scene(); //TODO remove these tests
    auto * testGO = newScene->CreateGameObject(); //TODO remove these tests
    testGO->AddComponent<MeshRenderer>(); //TODO remove these tests
    mLoadedScenes.emplace_back(newScene); //TODO remove these tests
}

void Engine::ProcessEvent(Event* theEvent) {
    switch(theEvent->mType)
    {
        case Event::INPUT:
            ProcessEventKeyboard(static_cast<KeyboardEvent*>(theEvent));
            break;
    }
}

void Engine::ProcessEventKeyboard(KeyboardEvent * theEvent) { //Only process special events needed for the engine
    std::cout<< "Got event\n";
    switch(theEvent->mVal)
    {
		case 27: //Escape key to exit
			exitStatus = 1;
			break;
    }
}