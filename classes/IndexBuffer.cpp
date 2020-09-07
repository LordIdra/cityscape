#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define raise_error(error)\
    std::cout << "=====[ERROR]=====" << "\n";\
    std::cout << "FILE: " << __FILE__ << "\n";\
    std::cout << "LINE: " << __LINE__ << "\n";\
    std::cout << error << "\n";\
    system("pause");


struct IndexBuffer
{
    unsigned int ID = 0;
    unsigned int size = 0;

    IndexBuffer(unsigned int data_size, void* data, unsigned int operation)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_size, data, operation);

        size = sizeof(data);
    }

    ~IndexBuffer()
    {
        glDeleteBuffers(1, &ID);
    }

    inline void Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    inline void Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};