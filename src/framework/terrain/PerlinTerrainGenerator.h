/* 
 * File:   PerinTerrainGenerator.h
 * Author: nathan
 *
 * Created on June 29, 2014, 12:30 AM
 */

#ifndef PERINTERRAINGENERATOR_H
#define	PERINTERRAINGENERATOR_H

#include "framework/Position.h"
#include "framework/Volume.h"
#include "noise/noise.h"
#include "noiseutils.h"

class PerlinTerrainGenerator  {
public:
    void init();
    VolumePtr generate(Position chunk);

private:    
    noise::module::Perlin perlin;
    noise::utils::NoiseMap heightMap;
    noise::utils::NoiseMapBuilderPlane heightMapBuilder;
    
    VolumePtr generateTerrain(Position position);
    VolumePtr generateBlock();
};

#endif	/* PERINTERRAINGENERATOR_H */

