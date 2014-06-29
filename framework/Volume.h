/* 
 * File:   Volume.h
 * Author: nathan
 *
 * Created on June 26, 2014, 5:48 PM
 */

#ifndef VOLUME_H
#define	VOLUME_H

#include <memory>

class Volume {
public:
    static const int XWIDTH = 16;
    static const int YWIDTH = 16;
    static const int ZWIDTH = 16;
    unsigned char voxels[XWIDTH][YWIDTH][ZWIDTH];
};

typedef std::shared_ptr<Volume> VolumePtr;

#endif	/* VOLUME_H */

