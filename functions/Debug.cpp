#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define raise_gl_error(error, file, line)\
    std::cout << "=====[ERROR]=====" << "\n";\
    std::cout << "FILE: " << file << "\n";\
    std::cout << "LINE: " << line << "\n";\
    std::cout << error << "\n";\
    system("pause");

#define get_errors(func)\
    get_gl_errors(__FILE__, __LINE__);

void get_gl_errors(std::string file, unsigned int line)
{
    unsigned int errorCode;
    while ((errorCode = glGetError()) != 0)
    {
        std::string error;
        switch (errorCode)
        {
            case 1280:      error = "invalid enum"; break;
            case 1281:      error = "invalid value"; break;
            case 1282:      error = "invalid operation"; break;
            case 1283:      error = "stack overflow"; break;
            case 1284:      error = "stack underflow"; break;
            case 1285:      error = "out of memory"; break;
            case 1286:      error = "invalid framebuffer operation"; break;
        }
        raise_gl_error(error, file, line);
    }
}