//
// Created by bios on 10/5/23.
//

#ifndef GAMEENGINE_IMGUILAYER_H
#define GAMEENGINE_IMGUILAYER_H
#include "../Core/Layer.h"


namespace VectorVertex {

    class ImguiLayer : public Layer {
    public:
        ImguiLayer();
        ~ImguiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void Begin();
        void End();
        void SetDarkThemeColors();

        uint32_t GetActiveWidgetID() const;

    };

} // VectorVertex

#endif //GAMEENGINE_IMGUILAYER_H
