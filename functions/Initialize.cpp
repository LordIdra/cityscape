#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define raise_error(error)\
    std::cout << "=====[ERROR]=====" << "\n";\
    std::cout << "FILE: " << __FILE__ << "\n";\
    std::cout << "LINE: " << __LINE__ << "\n";\
    std::cout << error << "\n";\
    system("pause");


void InitializeGLFW()
{
    if (!glfwInit())
    {
        raise_error("failed to initialize glfw");
        glfwTerminate();
    }
}

void SetVersion(unsigned int major, unsigned int minor, bool use_core_profile)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    if (use_core_profile) glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void InitializeGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        raise_error("failed to initialize glad");
    }

}