#include "../../Engine/src/VectorVertex/VectorVertex.h"

class SandBox: public VectorVertex::Application{
public:
    SandBox(){
        VV_WARN("Client Started!");

    }
    ~SandBox(){

    }
};

VectorVertex::Application* VectorVertex::CreateApplication() {
    return new SandBox();
}

int main(){

}