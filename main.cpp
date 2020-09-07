#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functions/Initialize.cpp>
#include <functions/Debug.cpp>

#include <classes/Shader.cpp>
#include <classes/VertexBuffer.cpp>
#include <classes/IndexBuffer.cpp>
#include <classes/VertexArray.cpp>
#include <classes/Texture.cpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define raise_error(error)\
    std::cout << "=====[ERROR]=====" << "\n";\
    std::cout << "FILE: " << __FILE__ << "\n";\
    std::cout << "LINE: " << __LINE__ << "\n";\
    std::cout << error << "\n";\
    system("pause");

float mix_percentage = 0.0;

/*
 * AUXILIARY FUNCTIONS
 */

//Resizes window and scales rendering operations accordingly
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

//Process user input (ie; keyboard/mouse input)
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

/*
 * MAIN FUNCTION
 */
int main()
{

    /* INITIALIZE GLFW/GLAD/SHADERS AND CREATE WINDOW */
    InitializeGLFW();
    SetVersion(3, 3, true);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        raise_error("failed to create window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    
    InitializeGLAD();

    Shader program("shaders/vertex.glsl", "shaders/fragment.glsl");


    /* INITIALIZE BUFFERS */
    //Generate cityscape
    float first_layer_vertices[24] = {
        -1.0f,  -1.0f,  0.0f,       0.1f, 0.1f, 0.2f,
        100.0f,   0.2f,   0.0f,       0.1f, 0.1f, 0.2f,
        100.0f,   -1.0f,  0.0f,       0.1f, 0.1f, 0.2f,
        -1.0f,  0.2f,  0.0f,        0.1f, 0.1f, 0.2f
    };

    unsigned int first_layer_indices[6] = {
        0, 1, 2,
        0, 1, 3
    };

    float second_layer_vertices[24] = {
        -1.0f,  -1.0f,  0.0f,       0.3f, 0.3f, 0.5f,
        50.0f,   0.35f,   0.0f,       0.3f, 0.3f, 0.5f,
        50.0f,   -1.0f,  0.0f,       0.3f, 0.3f, 0.5f,
        -1.0f,  0.35f,  0.0f,        0.3f, 0.3f, 0.5f
    };

    unsigned int second_layer_indices[6] = {
        0, 1, 2,
        0, 1, 3
    };

    std::vector<float>square_vertices1;
    std::vector<unsigned int>square_indices1;

    std::vector<float>square_vertices2;
    std::vector<unsigned int>square_indices2;

    //Probability of a square being generated increases with time since last square
    float square_probability = 100.0f;
    unsigned int triangle_count1 = 6;
    unsigned int vertex_count = 4;

    for (float& element : first_layer_vertices) square_vertices1.push_back(element);
    for (unsigned int& element : first_layer_indices) square_indices1.push_back(element);

    for (float& element : second_layer_vertices) square_vertices2.push_back(element);
    for (unsigned int& element : second_layer_indices) square_indices2.push_back(element);

    //FIRST LAYER
    for (float x = -1.0f; x < 100.0f; x += 0.01)
    {
        if ((rand() % 100) < square_probability)
        {
            //Reset probability
            square_probability = 100.0f;

            //Generate width/height
            float width = ((rand() % 5) + 3) / 100.0f;
            float height = ((rand() % 16) + 3) / 100.0f;

            //Generate vertices, appending them to vertices vector
            float new_vertices[24] = {
                x, 0.2f, 0.0f,                      0.1f, 0.1f, 0.2f,
                x + width, 0.2f, 0.0f,              0.1f, 0.1f, 0.2f,
                x, 0.2f + height, 0.0f,             0.1f, 0.1f, 0.2f,
                x + width, 0.2f + height, 0.0f,     0.1f, 0.1f, 0.2f
            };

            //Do the same with indices
            unsigned int new_indices[6] = {
                0 + vertex_count, 3 + vertex_count, 1 + vertex_count,
                0 + vertex_count, 3 + vertex_count, 2 + vertex_count
            };

            //Add generated arrays to vectors
            for (float& element : new_vertices) square_vertices1.push_back(element);
            for (unsigned int& element : new_indices) square_indices1.push_back(element);

            //Increment stuff
            x += width;
            x -= 0.01;
            triangle_count1 += 6;
            vertex_count += 4;
        }

        square_probability *= 1.35;
    }

    square_probability = 100.0f;
    unsigned int triangle_count2 = 6;
    vertex_count = 4;

    //SECOND LAYER
    for (float x = -1.0f; x < 50.0f; x += 0.01)
    {
        if ((rand() % 100) < square_probability)
        {
            //Reset probability
            square_probability = 100.0f;

            //Generate width/height
            float width = ((rand() % 5) + 3) / 100.0f;
            float height = ((rand() % 16) + 3) / 100.0f;

            //Generate vertices, appending them to vertices vector
            float new_vertices[24] = {
                x, 0.35f, 0.0f,                      0.3f, 0.3f, 0.5f,
                x + width, 0.35f, 0.0f,              0.3f, 0.3f, 0.5f,
                x, 0.35f + height, 0.0f,             0.3f, 0.3f, 0.5f,
                x + width, 0.35f + height, 0.0f,     0.3f, 0.3f, 0.5f
            };

            //Do the same with indices
            unsigned int new_indices[6] = {
                0 + vertex_count, 3 + vertex_count, 1 + vertex_count,
                0 + vertex_count, 3 + vertex_count, 2 + vertex_count
            };

            //Add generated arrays to vectors
            for (float& element : new_vertices) square_vertices2.push_back(element);
            for (unsigned int& element : new_indices) square_indices2.push_back(element);

            //Increment stuff
            x += width;
            x -= 0.01;
            triangle_count2 += 6;
            vertex_count += 4;
        }

        square_probability *= 1.35;
    }

    //Copy vertices into new array
    float *vertices1 = &square_vertices1[0];
    unsigned int *indices1 = &square_indices1[0];

    float *vertices2 = &square_vertices2[0];
    unsigned int *indices2 = &square_indices2[0];

    //Create VAO, VBO and EBO for first vertex set
    VertexArray vertex_array1;
    VertexBuffer vertex_buffer1(square_vertices1.size() * sizeof(float), vertices1, GL_STATIC_DRAW);
    IndexBuffer index_buffer1(square_indices1.size() * sizeof(unsigned int), indices1, GL_STATIC_DRAW);

    //0 = position, 1 = color
    vertex_array1.AddVertexAttribute(0, 3, GL_FLOAT, false, 6 * sizeof(float), 0);
    vertex_array1.AddVertexAttribute(1, 3, GL_FLOAT, false, 6 * sizeof(float), 3  *sizeof(float));

    //Create VAO, VBO and EBO for second vertex set
    VertexArray vertex_array2;
    VertexBuffer vertex_buffer2(square_vertices2.size() * sizeof(float), vertices2, GL_STATIC_DRAW);
    IndexBuffer index_buffer2(square_indices2.size() * sizeof(unsigned int), indices2, GL_STATIC_DRAW);

    //0 = position, 1 = color
    vertex_array2.AddVertexAttribute(0, 3, GL_FLOAT, false, 6 * sizeof(float), 0);
    vertex_array2.AddVertexAttribute(1, 3, GL_FLOAT, false, 6 * sizeof(float), 3  *sizeof(float));


    /* MAIN LOOP */
    while(!glfwWindowShouldClose(window))
    {
        /* PROCESS INPUT */
        processInput(window);


        /* RENDERING */
        //Use our precompiled shader
        program.Use();

        //Clear screen
        glClearColor(0.05f, 0.05f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Bind our second VAO and EBO
        vertex_array2.Bind();
        index_buffer2.Bind();

        //Bind uniforms
        glm::mat4 transform_matrix = glm::mat4(1.0f);
        transform_matrix = glm::translate(transform_matrix, glm::vec3(-glfwGetTime()/8, 0.0f, 0.0f));
        glUniformMatrix4fv(program.UniformLocation("transform_matrix"), 1, GL_FALSE, glm::value_ptr(transform_matrix));

        //Draw triangles
        glDrawElements(GL_TRIANGLES, triangle_count2, GL_UNSIGNED_INT, 0);

        //Bind our first VAO and EBO
        vertex_array1.Bind();
        index_buffer1.Bind();

        //Bind uniforms
        transform_matrix = glm::mat4(1.0f);
        transform_matrix = glm::translate(transform_matrix, glm::vec3(-glfwGetTime()/4, 0.0f, 0.0f));
        glUniformMatrix4fv(program.UniformLocation("transform_matrix"), 1, GL_FALSE, glm::value_ptr(transform_matrix));

        //Draw triangles
        glDrawElements(GL_TRIANGLES, triangle_count1, GL_UNSIGNED_INT, 0);

        /* FINAL OPERATIONS */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    /* WHEN WINDOW TERMINATED */
    glfwTerminate();
    return 0;
}