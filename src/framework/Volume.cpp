#include "Volume.h"

void Volume::setVoxel(int type, int x, int y, int z){
    this->voxels[x][y][z] = (unsigned char)type;
}