/* 
 * File:   Position.h
 * Author: nathan
 *
 * Created on June 28, 2014, 10:44 PM
 */

#ifndef POSITION_H
#define	POSITION_H

class Position {
public:
    float x;
    float y;
    float z;
    
    Position(float x = 0, float y = 0, float z = 0) : x(x), y(y),  z(z) {}
};

#endif	/* POSITION_H */

