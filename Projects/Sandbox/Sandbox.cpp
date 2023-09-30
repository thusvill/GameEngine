#include "../../Engine/src/VectorVertex/VectorVertex.h"


class SandBox: public VectorVertex::Application{
public:
    SandBox(){
    }
    ~SandBox(){

    }
};

VectorVertex::Application* VectorVertex::CreateApplication() {
    return new SandBox();
}


int main(int argc, char** argv) {
    //StartDebugging
    VectorVertex::Log::Init();

    auto app = VectorVertex::CreateApplication();
    VV_INFO("Started!");
    app->OnStart();
    delete app;
    return 0;
}


