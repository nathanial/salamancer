#version 330 core

uniform vec4 color;

out vec4 vs_color;

void main(void)
{
    vs_color = color;
}