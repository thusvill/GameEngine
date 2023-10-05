//
// Created by bios on 10/3/23.
//

#ifndef GAMEENGINE_LINUXWINDOW_H
#define GAMEENGINE_LINUXWINDOW_H
#include "../../Renderer/GraphicsContext.h"
#include "../../Core/Window.h"
#include "../../Core/Base.h"
#include "../../../vendor/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"

namespace VectorVertex {

    class LinuxWindow : public Window{
    public:
        LinuxWindow(const WindowProps& props);
        virtual ~LinuxWindow();

        void OnUpdate() override;
        unsigned int GetWidth() const override { return m_Data.Width; }
        unsigned int GetHeight() const override { return m_Data.Height; }

        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        virtual void* GetNativeWindow() const { return m_Window; }

        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    private:
        GLFWwindow* m_Window;
        Scope<GraphicsContext> m_Context;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
        };

        WindowData m_Data;

    };

} // VectorVertex

#endif //GAMEENGINE_LINUXWINDOW_H
