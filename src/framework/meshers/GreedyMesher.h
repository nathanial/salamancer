/* 
 * File:   GreedyMesher.h
 * Author: nathan
 *
 * Created on July 15, 2014, 12:12 AM
 */

#ifndef GREEDYMESHER_H
#define	GREEDYMESHER_H

#include <vector>
#include "../Volume.h"

typedef int Color;

class Point {
public:
    float first;
    float second;
    Point(float first, float second) : first(first), second(second) {
    }
};

typedef std::vector<float> FloatArray;

typedef FloatArray Vertex;

typedef std::vector<int> Face;

typedef std::vector<Point> Points;

typedef std::vector<Vertex> Vertices;

typedef std::vector<Face> Faces;

typedef std::vector<int> Int32Array;

typedef std::tuple<Vertices, Faces> VerticesAndFaces;


class GreedyMesher {
public:
    VerticesAndFaces mesh(VolumePtr volume);
};

#endif	/* GREEDYMESHER_H */

