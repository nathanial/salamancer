#version 330 core

in vec3 fragmentColor;

out vec3 vs_color;

void main(void)
{
    vs_color = fragmentColor;
}