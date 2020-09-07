#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec4 vertex_color;

uniform mat4 transform_matrix;

void main()
{
    gl_Position = transform_matrix * vec4(position.x, position.y, position.z, 1.0);
    vertex_color = vec4(color, 1.0);
}