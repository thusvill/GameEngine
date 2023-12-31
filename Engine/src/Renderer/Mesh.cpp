//
// Created by bios on 10/9/23.
//

#include "Mesh.h"
#include "RenderAPI.h"
#include "../Plattform/OpenGL/OpenGLMesh.h"
namespace VectorVertex {
    Ref<Mesh>
    Mesh::Create(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Ref<Texture>> &textures) {
        switch (RenderAPI::GetAPI()) {
            case RenderAPI::API::None: VV_CORE_WARN("VectorVertex is currently not support for nonGraphicsAPI!"); return nullptr;
            case RenderAPI::API::OpenGL: return CreateRef<OpenGLMesh>(vertices, indices,textures);
        }
    }
} // VectorVertex