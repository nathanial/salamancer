/* 
 * File:   GreedyMesher.h
 * Author: nathan
 *
 * Created on July 15, 2014, 12:12 AM
 */

#ifndef GREEDYMESHER_H
#define	GREEDYMESHER_H

#include "Mesher.h"

typedef std::vector<Vertex> Quad;
typedef std::vector<Quad> Quads;

class GreedyMesher {
public:
    virtual Quads mesh(VolumePtr volume);
};

#endif	/* GREEDYMESHER_H */

