/*  
 * File:   PerinTerrainGenerator.cpp
 * Author: nathan
 * 
 * Created on June 29, 2014, 12:30 AM
 */

#include "PerlinTerrainGenerator.h"
#include "noise/noise.h"
#include "noiseutils.h"
#include "framework/World.h"
#include <iostream>

using namespace noise;



void PerlinTerrainGenerator::init(){
    heightMapBuilder.SetSourceModule(perlin);
    heightMapBuilder.SetDestNoiseMap(heightMap);
    heightMapBuilder.SetDestSize(32*20,32*20);
}

VolumePtr PerlinTerrainGenerator::generateTerrain(Position position){
    VolumePtr volume(new Volume());

    heightMapBuilder.SetBounds(
            position.x*32,(position.x+1)*32,
            position.z*32,(position.z+1)*32
    );
    heightMapBuilder.Build();
    
    for(int x = 0; x < Volume::XWIDTH; x++){
        for(int z = 0; z < Volume::ZWIDTH; z++){
            float y = heightMap.GetValue(x, z);
            y += 2.0;
            y *= 10;
            y = round(y);
            std::cout << "Y: " << y << std::endl;
            if(y <= 0){
                y = 0;
            }
            if(y >= Volume::YWIDTH){
                y = Volume::YWIDTH-1;
            }
            volume->voxels[x][(int)y][z] = 1;
            for(int height = y; height >= 0; height--){
                volume->voxels[x][height][z] = 1;
            }
        }
    }
    return volume;
}

VolumePtr PerlinTerrainGenerator::generateBlock(){
    VolumePtr volume(new Volume());
    for(int i = 0; i < Volume::XWIDTH; i++){
        for(int j = 0; j < Volume::YWIDTH; j++){
            for(int k = 0; k < Volume::ZWIDTH; k++){
                volume->voxels[i][j][k] = 1;
            }
        }
    }
    return volume;
}

VolumePtr PerlinTerrainGenerator::generate(Position position) {
    if((int)position.y == World::YCHUNKS -1){
        return this->generateTerrain(position);
    } else {
        return this->generateBlock();
    }
}
