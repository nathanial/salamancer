/* 
 * File:   MonotoneMesher.h
 * Author: nathan
 *
 * Created on July 15, 2014, 12:12 AM
 */

#ifndef MONOTONEMESHER_H
#define	MONOTONEMESHER_H

#include "Mesher.h"

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

class MonotoneMesher {
public:
    virtual std::tuple<Vertices, Faces> mesh(VolumePtr volume);
private:
    void merge_run(MonotonePolygon *polygon, float v, float u_l, float u_r);
    void close_off(MonotonePolygon *poly, float value);
};


#endif	/* MONOTONEMESHER_H */

