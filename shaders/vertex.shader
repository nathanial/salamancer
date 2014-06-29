#version 330 core

layout (location = 0) in vec4 Vertex;
layout(location = 1) in vec3 vertexColor;
out vec3 fragmentColor;

uniform mat4 Transform;

void main(void)
{
    gl_Position = Transform * Vertex;
    fragmentColor = vertexColor;
}