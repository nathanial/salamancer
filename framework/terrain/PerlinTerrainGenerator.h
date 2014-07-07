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
#include "noise/noise.h"
#include "noiseutils.h"

class PerlinTerrainGenerator : public TerrainGenerator {
public:
    PerlinTerrainGenerator();
    ~PerlinTerrainGenerator();
    virtual VolumePtr generate(Position chunk);
    
    private:
        module::Perlin perlin;
        utils::NoiseMap heightMap;
        
        VolumePtr generateTerrain(Position position);
};

#endif	/* PERINTERRAINGENERATOR_H */

