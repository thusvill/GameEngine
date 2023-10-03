#include "../../Engine/src/VectorVertex/VectorVertex.h"

class NewLayer : public  VectorVertex::Layer{
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

VectorVertex::Application* VectorVertex::CreateApplication() {
    ApplicationSpecs specs;
    specs.Name = "Vector Vertex";
    return new SandBox(specs);
}


int main(int argc, char** argv) {
    //StartDebugging
    VectorVertex::Log::Init();
    auto app = VectorVertex::CreateApplication();
    VV_INFO("Started!");
    app->OnStart();
    app->Run();
    delete app;
    return 0;
}


