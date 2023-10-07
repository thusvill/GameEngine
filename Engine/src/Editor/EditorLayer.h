//
// Created by bios on 10/6/23.
//

#ifndef GAMEENGINE_EDITORLAYER_H
#define GAMEENGINE_EDITORLAYER_H
#include "../Core/Layer.h"
#include "../Renderer/RenderAPI.h"
#include "../Renderer/FrameBuffer.h"
#include "../Renderer/Camera.h"
namespace VectorVertex {

    class EditorLayer : public Layer {
    public:
        EditorLayer();
        ~EditorLayer() = default;
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnRender() override;

        virtual void OnImGuiRender() override;

        void BindFrameBuffer();
        void UnbindFrameBuffer();
        unsigned int GetFBORenderTextuer() {return m_FrameBuffer->GetRenderTexture();}
        Camera& GetEditorCamera() {return *m_EditorCamera;}

    private:
        Scope<Camera> m_EditorCamera;
        CameraProperties m_CameraProps;
        Scope<FrameBuffer> m_FrameBuffer;
    };

} // VectorVertex

#endif //GAMEENGINE_EDITORLAYER_H
