/**#include "../../Engine/vendor/glad/include/glad/glad.h"
#include "../../Engine/src/Plattform/OpenGL/GLAPI.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"


const char *vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

// Fragment Shader
const char *fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
)";

// Function to handle window resizing
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // Set GLFW to use the OpenGL core profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a GLFW window
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "OpenGL Triangle", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Make the OpenGL context of the window current
  glfwMakeContextCurrent(window);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Set the viewport size
  glViewport(0, 0, 800, 600);

  // Register the framebuffer size callback
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Vertex data for a triangle using the Vertex structure
  std::vector<VectorVertex::Vertex> vertices = {
      // Vertex 1
      {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f)},
      // Vertex 2
      {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
      // Vertex 3
      {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f)}
  };
  // Vertex Buffer Object (VBO)
   VectorVertex::OpenGLVBO vbo(vertices);


  // Vertex Array Object (VAO)
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Link VBO to VAO
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Element Buffer Object (EBO)
  // (not needed for a simple triangle, but included for completeness)
  GLuint EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // Compile Vertex Shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  // Check for vertex shader compilation errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
  }

  // Compile Fragment Shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  // Check for fragment shader compilation errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    std::cerr << "Fragment shader compilation failed:\n"
              << infoLog << std::endl;
  }

  // Link Shaders into a Shader Program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Check for shader program linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
  }

  // Use the shader program
  glUseProgram(shaderProgram);

  // Cleanup
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Main rendering loop
  while (!glfwWindowShouldClose(window)) {
    // Poll for and process events
    glfwPollEvents();

    // Clear the color buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    vbo.Bind();

    // Draw the triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vbo.Unbind();

    // Swap the front and back buffers
    glfwSwapBuffers(window);
  }

  // Cleanup
  glDeleteVertexArrays(1, &VAO);
  vbo.Delete();
  glDeleteProgram(shaderProgram);

  // Terminate GLFW
  glfwTerminate();

  return 0;
}
**/

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
    app->DockSpaceEnabled = true;
    VV_INFO("Started!");
    app->OnStart();
    app->Run();
    delete app;
    return 0;
}

