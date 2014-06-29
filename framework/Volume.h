/* 
 * File:   Volume.h
 * Author: nathan
 *
 * Created on June 26, 2014, 5:48 PM
 */

#ifndef VOLUME_H
#define	VOLUME_H

class Volume {
public:
    static const int XWIDTH = 32;
    static const int YWIDTH = 32;
    static const int ZWIDTH = 32;
    float voxels[XWIDTH][YWIDTH][ZWIDTH];
};

#endif	/* VOLUME_H */

