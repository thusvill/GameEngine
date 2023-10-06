#include "../../Engine/src/VectorVertex/VectorVertex.h"

class NewLayer : public  VectorVertex::Layer {
public:
    NewLayer(): Layer("NewLayer"){}
    virtual void OnImGuiRender() override;
};

void NewLayer::OnImGuiRender() {
    //ImGui::ShowDemoWindow();

    ImGui::Begin("Info");
    ImGui::Text("VectorVertex Engine V1.0");
    ImGui::SeparatorText("OpenGL Informations");
    ImGui::Text("  Vendor: %s", glGetString(GL_VENDOR));
    ImGui::Text("  Renderer: %s", glGetString(GL_RENDERER));
    ImGui::Text("  Version: %s", glGetString(GL_VERSION));
    ImGui::End();

    ImGui::Begin("Controls");
    ImGui::Checkbox("External Windows", &VectorVertex::Application::Get().ExternalViewpoertsEnabled);
    ImGui::Checkbox("Dock Space", &VectorVertex::Application::Get().DockSpaceEnabled);
    ImGui::End();
}


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
    //app->DockSpaceEnabled = false;
    app->ExternalViewpoertsEnabled = false;
    VV_INFO("Started!");
    VectorVertex::RenderAPI::SetAPI(VectorVertex::RenderAPI::API::OpenGL);
    app->OnStart();
    app->Run();
    delete app;
    return 0;
}

