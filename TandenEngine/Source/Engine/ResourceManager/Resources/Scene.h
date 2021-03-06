//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef HWENGINE_SCENE_H
#define HWENGINE_SCENE_H

#include <vector>
#include <iostream>

//Tanden Engine Classes
#include "../../Entity/GameObject.h"
#include "./Resource.h"

namespace TandenEngine {

    class Scene : public Resource {
    private:
        std::vector<std::unique_ptr<GameObject>> mGameObjects;

    public:

        Scene(); //Just create a new scene (generates scene setting file)

        GameObject *CreateGameObject();

        bool DestroyGameObject();

        GameObject *FindGameObject();

        void Update();

    };

}

#endif //HWENGINE_SCENE_H
