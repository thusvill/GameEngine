//
// Created by bios on 9/6/23.
//

#ifndef GAMEENGINE_APPLICATION_H
#define GAMEENGINE_APPLICATION_H

#include "Core.h"
#include "../Core/Log.h"
namespace VectorVertex {
    class Application {
    public:
        Application();
        virtual ~Application();
        virtual void OnStart();
        void Run();

    };
    // To be defined in CLIENT
    Application* CreateApplication();
}

#endif //GAMEENGINE_APPLICATION_H
