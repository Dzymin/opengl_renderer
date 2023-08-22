#include "pch.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.h"

void APIENTRY glDebugOutput(GLenum source, GLenum type, uint32_t id, GLenum severity,
    GLsizei length, const char* message, const void* userParam)
{
    //Ignore any unecessary notifications here 
    if (id == 131185)
        return;

    std::cout << "----------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:
            std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:
            std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:
            std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:
            std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "Type: Other"; break;
    } std::cout << std::endl;

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "Severity: High"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "Severity: Medium"; break;
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "Severity: Low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << "Severity: Notification"; break;
    } std::cout << std::endl;

    std::cout << std::endl;
}

int main() 
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW!";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
#ifdef APP_DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(1200, 720, "Hello World", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create a window!";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to load GL functions" << std::endl;
        glfwTerminate();
        return -1;
    }

#ifdef APP_DEBUG
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
#endif

    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };

    uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    uint32_t vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    uint32_t ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    Shader basicShader("res/Shaders/Basic.vertex", "res/Shaders/Basic.fragment");
    basicShader.Bind();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
