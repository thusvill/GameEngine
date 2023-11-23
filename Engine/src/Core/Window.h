//
// Created by bios on 10/1/23.
//

#ifndef GAMEENGINE_WINDOW_H
#define GAMEENGINE_WINDOW_H
#include "Base.h"

namespace VectorVertex {

    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string& title = "VectorVertex Engine",
                    uint32_t width = 1920,
                    uint32_t height = 1080)
                : Title(title), Width(width), Height(height)
        {
        }
    };

    class Window {
    public:
        virtual ~Window() = default;
        virtual void OnStart()=0;
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;
        virtual GLFWwindow* GetWindow() = 0;

        static Ref<Window> Create(const WindowProps& props = WindowProps());

    };

} // VectorVertex

#endif //GAMEENGINE_WINDOW_H
