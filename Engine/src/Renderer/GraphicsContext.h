//
// Created by bios on 9/30/23.
//

#ifndef GAMEENGINE_GRAPHICSCONTEXT_H
#define GAMEENGINE_GRAPHICSCONTEXT_H

#include "RenderAPI.h"
namespace VectorVertex {

    class GraphicsContext {
    public:
        virtual ~GraphicsContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() =  0;

        static Scope<GraphicsContext> Create(void* window);
    };

} // VectorVertex

#endif //GAMEENGINE_GRAPHICSCONTEXT_H
