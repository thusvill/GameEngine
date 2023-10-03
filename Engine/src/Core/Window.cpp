//
// Created by bios on 10/1/23.
//

#include "Window.h"
#include "../VectorVertex/Core.h"
#include "../Plattform/Linux/LinuxWindow.h"
namespace VectorVertex {
    Scope<Window> Window::Create(const VectorVertex::WindowProps &props) {
#ifdef VV_PLATFORM_LINUX
        VV_CORE_INFO("Platform Detected: Linux");
        return CreateScope<LinuxWindow>(props);
#else
        VV_CORE_ERROR("Unknown Platform!!");
        return nullptr
#endif
    }
} // VectorVertex