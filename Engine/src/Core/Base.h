//
// Created by bios on 9/12/23.
//
#pragma once
#ifndef GAMEENGINE_BASE_H
#define GAMEENGINE_BASE_H
#include "iostream"
#include "memory"
#include "vector"
#include "PlattformDetection.h"
#include "ErrorDetection.h"
#include "ImGuiLayer/ImguiLayer.h"


#define VV_DEBUG true

#define CHECK_OPENGL_ERROR() \
    do { \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            VV_CORE_ERROR("OpenGL error: {0}", error); \
        } \
    } while (false)


namespace VectorVertex{
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#endif //GAMEENGINE_BASE_H
