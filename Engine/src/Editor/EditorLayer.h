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
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;

        virtual void OnImGuiRender() override;
        virtual void OnRender() override;

        void BindFrameBuffer();
        void UnbindFrameBuffer();
        unsigned int GetFBORenderTextuer() {return m_FrameBuffer->GetRenderTexture();}
        Ref<Camera> GetEditorCamera() {
            if(m_EditorCamera != nullptr)
                return m_EditorCamera;
            else
                VV_CORE_ERROR("Editor Camera is NULL!");
        }
        EditorLayer* GetEditorLayer() {
            return this;
        }

        ShaderLibrary m_ShaderLibrary;
    private:
        Ref<Camera> m_EditorCamera;
        CameraProperties m_CameraProps;
        Scope<FrameBuffer> m_FrameBuffer;
    };

} // VectorVertex

#endif //GAMEENGINE_EDITORLAYER_H
