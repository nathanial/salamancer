/* 
 * File:   Mesher.h
 * Author: nathan
 *
 * Created on June 25, 2014, 2:12 AM
 */

#ifndef MESHER_H
#define	MESHER_H

#include <memory>
#include <vector>
#include <tuple>
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


#endif	/* MESHER_H */

