/* 
 * File:   Camera.h
 * Author: nathan
 *
 * Created on June 28, 2014, 11:01 PM
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include "Position.h"
#include "Rotation.h"
#include "vmath.h"

class Camera {

public:
    Camera();
    ~Camera();
    
    int windowWidth;
    int windowHeight;

    void rotate(float x, float y, float z);
    void move(float x, float y, float z);
    
    vmath::mat4 getMatrix();
    
private:
    Position position;
    Rotation rotation;
   
};

#endif	/* CAMERA_H */

