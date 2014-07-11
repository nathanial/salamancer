/* 
 * File:   MeshLoader.h
 * Author: nathan
 *
 * Created on July 11, 2014, 12:53 AM
 */

#ifndef MESHLOADER_H
#define	MESHLOADER_H

#include "Mesher.h"
#include <functional>
#include <string>

namespace MeshLoader {
    typedef std::tuple<Mesher::Vertices, Mesher::Faces> VerticesAndFaces;
    
    void loadMesh(std::string name, VerticesAndFaces verticesAndFaces);
};

#endif	/* MESHLOADER_H */

