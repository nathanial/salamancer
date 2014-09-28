/* 
 * File:   Position.h
 * Author: nathan
 *
 * Created on June 28, 2014, 10:44 PM
 */

#ifndef POSITION_H
#define	POSITION_H

#include "math.h"

#include <unordered_map>


class Position {
public:
    int x;
    int y;
    int z;
    
    Position(int x = 0, int y = 0, int z = 0) : x(x), y(y),  z(z) {}

    bool operator==(const Position &ref) const {
        return (this->x == ref.x) && (this->y == ref.y) && (this->z == ref.z);
    }
};

namespace std {

    template <>
    class hash<Position> {
    public:
        size_t operator()(const Position &p) const {
            return hash<int>()(p.x) ^ hash<int>()(p.y) ^ hash<int>()(p.z);
        }
    };
}


#endif	/* POSITION_H */

