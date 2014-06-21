#version 330 core

layout (location = 0) in vec4 Vertex;

uniform mat4 Transform;

void main(void)
{
    gl_Position = Transform * Vertex;
}