/* 
 * File:   shapes.h
 * Author: nathan
 *
 * Created on June 20, 2014, 10:28 PM
 */

#ifndef SHAPES_H
#define	SHAPES_H

#define SHAPE_Z 1

namespace shapes {
    static const float triangle[] = {
        0.25, -0.25, 1, 1.0,
        -0.25, -0.25, 1, 1.0,
        0.25,  0.25, 1, 1.0 
    };
    
    static const float square[] = {
        -1, -1, - SHAPE_Z, 1,
        -1, 1, - SHAPE_Z, 1.0,
        1, 1, -SHAPE_Z, 1.0,
        
        -1, -1, - SHAPE_Z, 1.0,
        1, -1, - SHAPE_Z, 1.0,
        1, 1, - SHAPE_Z, 1.0
    };
    
    static const float cube[] = {
        
    };
    
};

#endif	/* SHAPES_H */

