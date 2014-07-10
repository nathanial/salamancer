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

module::Perlin perlin;


VolumePtr generateTerrain(Position position){
    VolumePtr volume(new Volume());
    
    std::cout << "+++++++++++++++++++++++++++++++Position: " << position.x << " " << position.y << " " << position.z << std::endl;
    
    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule(perlin);
    heightMapBuilder.SetDestNoiseMap(heightMap);
    heightMapBuilder.SetDestSize(90,90);
    heightMapBuilder.SetBounds(
            position.x*4,(position.x+1)*4,
            position.z*4,(position.z+1)*4
    );
    heightMapBuilder.Build();
    
    for(int x = 0; x < Volume::XWIDTH; x++){
        for(int z = 0; z < Volume::ZWIDTH; z++){
            float y = heightMap.GetValue(x, z);
            y = (y+1.5)*4;
            if(y <= 0){
                std::cout << "1 Ooops: " << heightMap.GetValue(x,z) + 1.5 << std::endl;
                y = 0;
            }
            if(y >= 16){
                std::cout << "2 Ooops: " << heightMap.GetValue(x,z) + 1.5 << std::endl;
                y = 15;
            }
            volume->voxels[x][(int)y][z] = 1;
            for(int height = y; height >= 0; height--){
                volume->voxels[x][height][z] = 1;
            }
        }
    }
    return volume;
}

VolumePtr generateBlock(){
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
        return generateTerrain(position);
    } else {
        return generateBlock();
    }
}
