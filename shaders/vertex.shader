#version 330 core

layout (location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;

smooth out vec4 interpColor;

uniform vec3 dirToLight;
uniform vec4 lightIntensity;

uniform mat4 Transform;
uniform mat3 normalModelToCameraMatrix;

void main(void)
{
    vec3 normal = vec3(0,0,1.0);

    gl_Position = Transform * vec4(position, 1.0);

    vec3 normCamSpace = normalize(normalModelToCameraMatrix * normal);

    float cosAngIncidence = dot(normCamSpace, dirToLight);
    cosAngIncidence = clamp(cosAngIncidence, 0, 1);

    interpColor = lightIntensity * cosAngIncidence;
}