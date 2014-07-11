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
    void attach(GLuint program);
    void detach(GLuint program);
private:    
    DISALLOW_COPY_AND_ASSIGN(Shader);
    
    std::string path;
    bool compiled = false;
    GLuint shaderType;
    GLuint shaderHandle;
    
};

#endif	/* SHADER_H */

