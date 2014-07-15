/* 
 * File:   GreedyMesher.cpp
 * Author: nathan
 * 
 * Created on July 15, 2014, 12:12 AM
 */

#include "GreedyMesher.h"

Quads GreedyMesher::mesh(VolumePtr volume) {
    int dims[] = {Volume::XWIDTH, Volume::YWIDTH, Volume::ZWIDTH};

    auto f = [&](int x, int y, int z) {
        return volume->voxels[x][y][z];
    };

    //Sweep over 3-axes
    Quads quads;
    for (int d = 0; d < 3; d++) {
        int i, j, k, l, w, h
                , u = (d + 1) % 3
                , v = (d + 2) % 3;
        int x[3] = {0};
        int q[3] = {0};
        Int32Array mask(dims[u] * dims[v]);
        q[d] = 1;

        for (x[d] = -1; x[d] < dims[d];) {
            //Compute mask
            int n = 0;
            for (x[v] = 0; x[v] < dims[v]; ++x[v])
                for (x[u] = 0; x[u] < dims[u]; ++x[u]) {
                    mask[n++] =
                            (0 <= x[d] ? f(x[0], x[1], x[2]) : false) !=
                            (x[d] < dims[d] - 1 ? f(x[0] + q[0], x[1] + q[1], x[2] + q[2]) : false);
                }
            //Increment x[d]
            ++x[d];
            //Generate mesh for mask using lexicographic ordering
            n = 0;
            for (j = 0; j < dims[v]; ++j)
                for (i = 0; i < dims[u];) {
                    if (mask[n]) {
                        //Compute width
                        for (w = 1; mask[n + w] && i + w < dims[u]; ++w) {
                        }
                        //Compute height (this is slightly awkward
                        bool done = false;
                        for (h = 1; j + h < dims[v]; ++h) {
                            for (k = 0; k < w; ++k) {
                                if (!mask[n + k + h * dims[u]]) {
                                    done = true;
                                    break;
                                }
                            }
                            if (done) {
                                break;
                            }
                        }
                        //Add quad
                        x[u] = i;
                        x[v] = j;
                        int du[3] = {0};
                        du[u] = w;
                        int dv[3] = {0};
                        dv[v] = h;
                        quads.push_back(Quad({
                            Vertex({x[0], x[1], x[2]}),
                            Vertex({x[0] + du[0], x[1] + du[1], x[2] + du[2]}),
                            Vertex({x[0] + du[0] + dv[0], x[1] + du[1] + dv[1], x[2] + du[2] + dv[2]}),
                            Vertex({x[0] + dv[0], x[1] + dv[1], x[2] + dv[2]})
                        }));
                        //Zero-out mask
                        for (l = 0; l < h; ++l)
                            for (k = 0; k < w; ++k) {
                                mask[n + k + l * dims[u]] = false;
                            }
                        //Increment counters and continue
                        i += w;
                        n += w;
                    } else {
                        ++i;
                        ++n;
                    }
                }
        }
    }
    
    return quads;
}