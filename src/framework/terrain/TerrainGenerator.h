/* 
 * File:   TerrainGenerator.h
 * Author: nathan
 *
 * Created on June 29, 2014, 12:30 AM
 */

#ifndef TERRAINGENERATOR_H
#define	TERRAINGENERATOR_H

#include "framework/Volume.h"
#include "framework/Position.h"

class TerrainGenerator {
public:
    virtual VolumePtr generate(Position chunk) = 0;
};

#endif	/* TERRAINGENERATOR_H */

