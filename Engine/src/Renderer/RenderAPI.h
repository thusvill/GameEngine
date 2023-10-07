//
// Created by bios on 9/12/23.
//

#ifndef GAMEENGINE_RENDERAPI_H
#define GAMEENGINE_RENDERAPI_H
#include "../VectorVertex/Core.h"
#include "GraphicsContext.h"

namespace VectorVertex {
    class RenderAPI {
    public:

        enum class API{
            None = 0, OpenGL = 1
        };
        static std::string ApiToString(API api) {
            static const std::unordered_map<API, std::string> apiStrings = {
                    {API::None, "None"},
                    {API::OpenGL, "OpenGL"}
            };

            auto it = apiStrings.find(api);
            if (it != apiStrings.end()) {
                return it->second;
            }

            return "UNKNOWN";
        }
        static void SetAPI(API newAPI){
            m_RenderAPI = newAPI;
            VV_CORE_WARN("Render API changed to : {}", ApiToString(m_RenderAPI));
        }
    public:
        inline static API GetAPI() { return m_RenderAPI;}

    private:
        static API m_RenderAPI;

    };
}

#endif //GAMEENGINE_RENDERAPI_H
