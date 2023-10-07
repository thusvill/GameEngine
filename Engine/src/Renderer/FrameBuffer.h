//
// Created by bios on 10/6/23.
//

#ifndef GAMEENGINE_FRAMEBUFFER_H
#define GAMEENGINE_FRAMEBUFFER_H
#include "RenderAPI.h"
namespace VectorVertex {

    class FrameBuffer {
    public:
        static Scope<FrameBuffer> Create(int width, int height);
        virtual ~FrameBuffer() = default;

        virtual void Resize(int newWidth, int newHeight) = 0;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual unsigned int GetRenderTexture() = 0;
    };

} // VectorVertex

#endif //GAMEENGINE_FRAMEBUFFER_H
