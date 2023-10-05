#include "../../Engine/src/VectorVertex/VectorVertex.h"

class NewLayer : public  VectorVertex::Layer {
public:
    NewLayer(): Layer("NewLayer"){}
    virtual void OnAttach() override{
        VV_INFO("Layer Attached!");
    }
    virtual void OnUpdate() override{
    }
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
    m_Specs.Name = "VV";
    auto app = VectorVertex::CreateApplication(m_Specs);
    VV_INFO("Started!");
    VectorVertex::RenderAPI::SetAPI(VectorVertex::RenderAPI::API::OpenGL);
    app->OnStart();
    app->Run();
    delete app;
    return 0;
}


