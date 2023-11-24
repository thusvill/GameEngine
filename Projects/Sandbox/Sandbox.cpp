#include "../../Engine/src/VectorVertex/VectorVertex.h"
#include "../../Engine/src/VectorVertex/Renderer.h"

class NewLayer : public  VectorVertex::Layer {
public:
    NewLayer(): Layer("NewLayer"){}
};



class SandBox: public VectorVertex::Application{
public:
    SandBox(const ApplicationSpecs& specifications): VectorVertex::Application(specifications) {
        PushLayer(new NewLayer());

    }
    ~SandBox(){

    }
};

VectorVertex::Application* VectorVertex::CreateApplication(ApplicationSpecs& specs) {
    return new SandBox(specs);
}


int main(int argc, char** argv) {
    //StartDebugging
    VectorVertex::Log::Init();
    ApplicationSpecs m_Specs;
    m_Specs.width = 1920;
    m_Specs.height = 1024;
    m_Specs.Name = "VectorVertex";
    VectorVertex::RenderAPI::SetAPI(VectorVertex::RenderAPI::API::OpenGL);
    auto app = VectorVertex::CreateApplication(m_Specs);
    app->DockSpaceEnabled = false;
    VV_INFO("Started!");
    app->OnStart();
    app->Run();
    delete app;
    return 0;
}

