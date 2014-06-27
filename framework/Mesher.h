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
#include "Volume.h"

namespace Mesher {
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

    typedef std::vector<Point> Points;

    typedef std::vector<Vertex> Vertices;

    typedef std::vector<Vertex> Faces;

    typedef std::unique_ptr<int[]> Int32Array;
    
    class MonotonePolygon {
    public:
        Color color;
        Points left;
        Points right;

        MonotonePolygon(Color c, float v, float ul, float ur){
            this->color = c;
            this->left.push_back(Point(ul, v));
            this->right.push_back(Point(ur, v));
        }
    };

    typedef std::vector<MonotonePolygon> Polygons;
    
    void merge_run(MonotonePolygon &polygon, float v, float u_l, float u_r);
    void close_off(MonotonePolygon &poly, float value);
    std::tuple<Vertices, Faces> mesh(Volume volume, int dims[3]);
};

#endif	/* MESHER_H */

