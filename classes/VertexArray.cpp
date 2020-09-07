#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define raise_error(error)\
    std::cout << "=====[ERROR]=====" << "\n";\
    std::cout << "FILE: " << __FILE__ << "\n";\
    std::cout << "LINE: " << __LINE__ << "\n";\
    std::cout << error << "\n";\
    system("pause");


struct VertexArray
{
    unsigned int ID = 0;

    VertexArray()
    {
        glGenVertexArrays(1, &ID);
        glBindVertexArray(ID);
    }

    ~VertexArray()
    {
        glDeleteVertexArrays(1, &ID);
    }

    inline void Bind()
    {
        glBindVertexArray(ID);
    }

    inline void Unbind()
    {
        glBindVertexArray(0);
    }

    void AddVertexAttribute(unsigned int layout_position, unsigned int byte_size, unsigned int type,
        bool normalized, unsigned int byte_stride, unsigned int byte_offset)
    {
        glBindVertexArray(ID);
        glVertexAttribPointer(
            layout_position, 
            byte_size, 
            type, 
            normalized, 
            byte_stride, 
            (void*)byte_offset);
        
        glEnableVertexAttribArray(layout_position);
        glBindVertexArray(0);
    }
};