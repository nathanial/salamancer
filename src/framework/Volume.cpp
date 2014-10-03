#include "Volume.h"

void Volume::setVoxel(Position p, int type){
    this->voxels[p.x][p.y][p.z] = (unsigned char)type;
}