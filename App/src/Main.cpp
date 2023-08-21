#include "pch.h"
#include "GLFW/glfw3.h"

int main() 
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW!";
        return -1;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);

    if (!window)
    {
        std::cout << "Failed to create a window!";
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
