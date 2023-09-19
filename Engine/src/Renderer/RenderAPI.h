//
// Created by bios on 9/12/23.
//

#ifndef GAMEENGINE_RENDERAPI_H
#define GAMEENGINE_RENDERAPI_H
#include "../VectorVertex/Core.h"

namespace VectorVertex {
    class RenderAPI {
    public:
        enum class API{
            None = 0, OpenGL = 1
        };
    public:
        inline static API GetAPI() {return m_RenderAPI;}

    private:
        static API m_RenderAPI;

    };
}

#endif //GAMEENGINE_RENDERAPI_H
