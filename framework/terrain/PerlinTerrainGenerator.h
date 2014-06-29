/* 
 * File:   PerinTerrainGenerator.h
 * Author: nathan
 *
 * Created on June 29, 2014, 12:30 AM
 */

#ifndef PERINTERRAINGENERATOR_H
#define	PERINTERRAINGENERATOR_H

#include "TerrainGenerator.h"
#include "framework/Volume.h"

class PerlinTerrainGenerator : public TerrainGenerator {
public:
    virtual VolumePtr generate(Position chunk);
};

#endif	/* PERINTERRAINGENERATOR_H */

