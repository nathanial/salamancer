/* 
 * File:   Mesher.cpp
 * Author: nathan
 * 
 * Created on June 25, 2014, 2:12 AM
 */

#include <memory>
#include <vector>
#include <tuple>

#include "Mesher.h"
#include "util.h"

typedef int Color;

struct Point {
    float first;
    float second;
    Point(float first, float second) : first(first), second(second) {
    }
};

struct Vertex {
    
};

struct Face {
    
};


typedef std::vector<Point> Points;

typedef std::vector<Vertex> Vertices;

typedef std::vector<Face> Faces;

typedef std::unique_ptr<int[]> Int32Array;


struct MonotonePolygon {
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

void merge_run(MonotonePolygon &polygon, auto v, auto u_l, auto u_r){
    
}

void close_off(auto a, auto b){
    
}

void mesh(auto volume, auto dims){
    auto f = [&](int i, int j, int k){
        return volume[i + dims[0] * (j + dims[1] * k)];
    };
    
    Vertices vertices;
    Faces faces;
    
    for(int axis = 0; axis < 3; axis++){
        int i,j,k;
        int u = (axis+1)%3; //u and v are orthogonal directions to the axis
        int v = (axis+2)%3;
        int x[3] = {0};
        int q[3] = {0};
        Int32Array runs(new int[2 * (dims[u]+1)]);
        Int32Array frontier(new int[dims[u]]); //frontier is a list of pointers to polygons
        Int32Array next_frontier(new int[dims[u]]);
        Int32Array left_index(new int[2 * dims[v]]);
        Int32Array right_index(new int[2 * dims[v]]);
        Int32Array stack(new int[24 * dims[v]]);
        int delta[][2] = {{0,0},{0,0}};
        
        //q points along axis
        q[axis] = 1;
        
        for(x[axis] = -1; x[axis] < dims[axis]; ){
            int n = 0;
            Polygons polygons;
            int nf = 0;
            
            for(x[v] = 0; x[v] < dims[v]; x[v]++){
                int nr = 0;
                int p = 0;
                int c = 0;
                //make one pass over the u-scan line of the volume to run-length encode polygon
                for(x[u] = 0; x[u] < dims[u]; x[u]++, p = c){
                    //compute the type of this face
                    auto a = (0 <= x[axis] ? f(x[0], x[1], x[2]) : 0);
                    auto b = (x[axis] < dims[axis]-1 ? f(x[0] + q[0], x[1] + q[1], x[2] + q[2]) : 0);
                    c = a;
                    if((!a) == (!b)){
                        c = 0;
                    } else if(!a) {
                        c = -b;
                    }
                    
                    //if cell doesn't match, start a new run
                    if(p != c){
                        runs[nr++] = x[u];
                        runs[nr++] = c;
                    }
                }
                
                //add sentinal run
                runs[nr++] = dims[u];
                runs[nr++] = 0;
                
                //update the frontier by merging runs
                int fp = 0;
                for(int i = 0, j = 0; i < nf && j < nr-2; ){
                    auto p = polygons[frontier[i]];
                    auto p_1 = p.left.at(p.left.size()-1).first;
                    auto p_r = p.right.at(p.right.size()-1).first;
                    auto p_c = p.color;
                    auto r_l = runs[j]; //start of run
                    auto r_r = runs[j+2]; //end of run
                    auto r_c = runs[j+1]; //color of run
                    //check if we can merge run with polygon
                    if(r_r > p_1 && p_r > r_l && r_c == p_c){
                        merge_run(p, x[v], r_l, r_r);
                        next_frontier[fp++] = frontier[i];
                        ++i;
                        j += 2;
                    } else {
                        //check if we need to advance the run pointer
                        if(r_r <= p_r){
                            if(r_c){
                                MonotonePolygon n_poly(r_c, x[v], r_l, r_r);
                                next_frontier[fp++] = polygons.size();
                                polygons.push_back(n_poly);
                            }
                            j += 2;
                        }
                        if(p_r <= r_r){
                            close_off(p, x[v]);
                            i++;
                        }
                    }
                }
            }
        }
    }
}