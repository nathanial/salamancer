/*  
 * File:   PerinTerrainGenerator.cpp
 * Author: nathan
 * 
 * Created on June 29, 2014, 12:30 AM
 */

#include "PerlinTerrainGenerator.h"
#include "noise/noise.h"
#include "framework/World.h"
#include <iostream>


VolumePtr PerlinTerrainGenerator::generate(Position position) {
    noise::module::Perlin perlin;
    
    Volume *v = new Volume();
    VolumePtr volume(v);
    
    auto scale = [](float x, float fromLow, float fromHigh, float toLow, float toHigh ) {
        return ( x - fromLow ) * ( toHigh - toLow ) / ( fromHigh - fromLow ) + toLow;
    };
    
    int width = Volume::XWIDTH;
    
    std::cout << position.y << std::endl;
    if((int)position.y == World::YCHUNKS -1){
        std::cout << "HERE" << std::endl;
        float floor = 0;
        float ceiling = 20;
        float divisor = 50;
        for(int i = 0; i < Volume::XWIDTH; i++){
            for(int j = 0; j < Volume::ZWIDTH; j++){
                double n = perlin.GetValue(i / divisor, 1,  j / divisor);
                int y = scale(n, -1, 1, floor, ceiling);
                int xidx = abs((width + i % width) % width);
                int yidx = abs((width + y % width) % width);
                int zidx = abs((width + j % width) % width);
                if(xidx >= width || yidx >= width || zidx >= width){
                    continue;
                }
                volume->voxels[xidx][yidx][zidx] = 1;
            }
        }
    } else {
        for(int i = 0; i < Volume::XWIDTH; i++){
            for(int j = 0; j < Volume::YWIDTH; j++){
                for(int k = 0; k < Volume::ZWIDTH; k++){
                    volume->voxels[i][j][k] = 1;
                }
            }
        }
    }
     
    
//    for(int x = 0; x < Volume::XWIDTH; x++){
//        for(int y = 0; y < Volume::YWIDTH; y++){
//            for(int z = 0; z < Volume::ZWIDTH; z++){
//                int d = rand() % 100;
//                if(d > 50){
//                    volume->voxels[x][y][z] = 1;
//                }
//            }
//        }
//    }
    
    return volume;
}
