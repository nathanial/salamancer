/* 
 * File:   Camera.cpp
 * Author: nathan
 * 
 * Created on June 28, 2014, 11:01 PM
 */

#include "Camera.h"

Camera::Camera() : position(0,0,-500), rotation(0,0) {
}

Camera::~Camera() {
}

void Camera::rotate(float x, float y, float z) {
    this->rotation.x += x;
    this->rotation.y += y;
    this->rotation.z += z;
}

void Camera::move(float x, float y, float z){
    this->position.x += x;
    this->position.y += y;
    this->position.z += z;
}

vmath::mat4 Camera::getMatrix() {
    float aspect = (float)this->windowWidth / (float)this->windowHeight;
    vmath::mat4 matrix(vmath::mat4::identity());
    matrix *= vmath::perspective(1, aspect, 0.1f, 10000.0f);
    matrix *= vmath::translate(position.x, position.y, position.z);
    matrix *= vmath::rotate(rotation.x, 1.0f, 0.0f, 0.0f);
    matrix *= vmath::rotate(rotation.y, 0.0f, 1.0f, 0.0f);
    matrix *= vmath::rotate(rotation.z, 0.0f, 0.0f, 1.0f);
    return matrix;
}

