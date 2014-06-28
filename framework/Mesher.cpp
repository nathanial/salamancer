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
#include "Volume.h"
#include "util.h"

void Mesher::merge_run(MonotonePolygon &polygon, float v, float u_l, float u_r){
    auto l = polygon.left[polygon.left.size()-1].first;
    auto r = polygon.right[polygon.right.size()-1].first;
    if(1 != u_l){
        polygon.left.push_back(Point(l, v));
        polygon.left.push_back(Point(u_l, v));
    }
    if(r != u_r){
        polygon.right.push_back(Point(r, v));
        polygon.right.push_back(Point(u_r, v));
    }
}

void Mesher::close_off(MonotonePolygon &poly, float value){
    poly.left.push_back(Point(poly.left[poly.left.size()-1].first, value));
    poly.right.push_back(Point(poly.right[poly.right.size()-1].first, value));
}


std::tuple<Mesher::Vertices, Mesher::Faces> Mesher::mesh(const Volume &volume, int dims[3]){
    auto f = [&](int x, int y, int z){
        return volume.voxels[x][y][z];
    };
    
    Vertices vertices;
    Faces faces;
    
    for(int d = 0; d < 3; d++){
        int i = 0,j = 0,k = 0;
        int u = (d+1)%3; //u and v are orthogonal directions to the axis
        int v = (d+2)%3;
        int x[3] = {0};
        int q[3] = {0};
        Int32Array runs(2 * (dims[u]+1));
        Int32Array frontier(dims[u]); //frontier is a list of pointers to polygons
        Int32Array next_frontier(dims[u]);
        Int32Array left_index(2 * dims[v]);
        Int32Array right_index(2 * dims[v]);
        Int32Array stack(24 * dims[v]);
        int delta[][2] = {{0,0},{0,0}};
        
        //q points along axis
        q[d] = 1;
        
        for(x[d] = -1; x[d] < dims[d]; ){
            Polygons polygons;
            int nf = 0;
            int n = 0;
            
            for(x[v] = 0; x[v] < dims[v]; x[v]++){
                //make one pass over the u-scan line of the volume to run-length encode polygon
                int nr = 0, p = 0, c = 0;
                for(x[u] = 0; x[u] < dims[u]; x[u]++, p = c){
                    //compute the type of this face
                    int a = (0 <= x[d] ? f(x[0], x[1], x[2]) : 0);
                    int b = (x[d] < dims[d]-1 ? f(x[0] + q[0], x[1] + q[1], x[2] + q[2]) : 0);
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
                for(i = 0, j = 0; i < nf && j < nr-2; ){
                    MonotonePolygon& p = polygons[frontier[i]];
                    auto p_1 = p.left[p.left.size()-1].first;
                    auto p_r = p.right[p.right.size()-1].first;
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
                            if(!!r_c){
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
                
                //close off any residual polygons
                for(; i < nf; i++){
                    MonotonePolygon &polygon = polygons[frontier[i]];
                    close_off(polygon, x[v]);
                }
                
                //add any extra runs to frontier
                for(; j < nr-2; j += 2){
                    int r_l = runs[j];
                    int r_r = runs[j+2];
                    int r_c = runs[j+1];
                    if(!!r_c){
                        MonotonePolygon n_poly(r_c, x[v], r_l, r_r);
                        next_frontier[fp++] = polygons.size();
                        polygons.push_back(n_poly);
                    }
                }

                Int32Array tmp = next_frontier;
                next_frontier = frontier;
                frontier = tmp;
                nf = fp;
            }
            
            //close off frontier
            for(i = 0; i < nf; i++){
                MonotonePolygon& p = polygons[frontier[i]];
                close_off(p, dims[v]);
            }
            
            //monotone subdivision of polygon is complete at this point
            x[d]++;
            
            //now we just need to triangulate each monotone polygon
            for(i = 0; i < polygons.size(); i++){
                MonotonePolygon& p = polygons[i];
                Color c = p.color;
                bool flipped = false;
                
                if(c < 0){
                    flipped = true;
                    c = -c;
                }
                
                for(j = 0; j < p.left.size(); j++){
                    left_index[j] = vertices.size();
                    Vertex y = {0.0,0.0,0.0};
                    Point z = p.left[j];
                    y[d] = x[d];
                    y[u] = z.first;
                    y[v] = z.second;
                    vertices.push_back(y);
                }
                
                for(j = 0; j < p.right.size(); j++){
                    right_index[j] = vertices.size();
                    Vertex y = {0.0,0.0,0.0};
                    Point z = p.right[j];
                    y[d] = x[d];
                    y[u] = z.first;
                    y[v] = z.second;
                    vertices.push_back(y);
                }
                
                //triangulate the monotone polygon
                int bottom = 0;
                int top = 0;
                int l_i = 1;
                int r_i = 1;
                bool side = true;
                
                stack[top++] = left_index[0];
                stack[top++] = p.left[0].first;
                stack[top++] = p.left[0].second;
                
                stack[top++] = right_index[0];
                stack[top++] = p.right[0].first;
                stack[top++] = p.right[0].second;
                
                while(l_i < p.left.size() || r_i < p.right.size()){
                    bool n_side = false;
                    
                    if(l_i == p.left.size()){
                        n_side = true;
                    } else if(r_i != p.right.size()) {
                        Point l = p.left[l_i];
                        Point r = p.right[r_i];
                        n_side = l.second > r.second;
                    }
                    auto idx = n_side ? right_index[r_i] : left_index[l_i];
                    Point vert = n_side ? p.right[r_i] : p.left[l_i];
                    if(n_side != side){
                        //opposite side
                        while(bottom+3 < top){
                            if(flipped == n_side){
                                faces.push_back({stack[bottom], stack[bottom+3], idx, c});
                            } else {
                                faces.push_back({stack[bottom+3], stack[bottom], idx, c});
                            }
                            bottom += 3;
                        }
                    } else {
                        while(bottom+3 < top){
                            for(int j = 0; j < 2; j++){
                                for(int k = 0; k < 2; k++){
                                    if(k == 0){
                                        delta[j][k] = stack[top-3*(j+1)+k+1] - vert.first;
                                    } else {
                                        delta[j][k] = stack[top-3*(j+1)+k+1] - vert.second;
                                    }
                                }
                            }
                            auto det = delta[0][0] * delta[1][1] - delta[1][0] * delta[0][1];
                            if(n_side == (det > 0)){
                                break;
                            }
                            if(det != 0){
                                if(flipped == n_side){
                                    faces.push_back({stack[top-3], stack[top-6], idx, c});
                                } else {
                                    faces.push_back({stack[top-6], stack[top-3], idx, c});
                                }
                            }
                            top -= 3;
                        }
                    }
                    stack[top++] = idx;
                    stack[top++] = vert.first;
                    stack[top++] = vert.second;

                    if(n_side){
                        r_i++;
                    } else {
                        l_i++;
                    }
                    side = n_side;
                }
            }
        }
    }
    
    return std::tuple<Vertices, Faces>(vertices, faces);
}