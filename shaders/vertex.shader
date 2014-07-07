#version 330 core

layout (location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 normal;

smooth out vec4 interpColor;

uniform vec3 dirToLight;

uniform mat4 Transform;
uniform mat3 normalModelToCameraMatrix;

void main(void)
{
    gl_Position = Transform * vec4(position, 1.0);

    vec3 normCamSpace = normalize(normalModelToCameraMatrix * normal);

    float cosAngIncidence = dot(normCamSpace, dirToLight);
    cosAngIncidence = clamp(cosAngIncidence, 0, 1);

    interpColor = vec4(vertexColor, 1.0);
    
}