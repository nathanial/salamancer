/* 
 * File:   Shader.h
 * Author: nathan
 *
 * Created on June 21, 2014, 8:11 PM
 */

#ifndef SHADER_H
#define	SHADER_H
#include "util.h"

typedef unsigned int	GLuint;	

class Shader {
public:
    Shader(GLuint shaderType, const char *path);
    ~Shader();
    void compile();
private:    
    DISALLOW_COPY_AND_ASSIGN(Shader);
    
    std::string path;
    GLuint shaderType;
};

#endif	/* SHADER_H */

