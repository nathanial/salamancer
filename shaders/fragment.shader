#version 330 core

smooth in vec4 interpColor;

out vec4 vs_color;

void main(void)
{
    vs_color = interpColor;
}