/* 
 * File:   GLProgram.h
 * Author: nathan
 *
 * Created on June 21, 2014, 8:00 PM
 */

#ifndef GLPROGRAM_H
#define	GLPROGRAM_H

#include "util.h"
#include <vector>
#include <memory>

#include "Shader.h"

typedef std::shared_ptr<Shader> ShaderPtr;
typedef unsigned int	GLuint;	
typedef int GLint;

class GLProgram {
public:
    GLProgram();
    ~GLProgram();
    
    void loadVertexShader(const char *path);
    void loadFragmentShader(const char *path);
    void compileAndLink();
    void use();
    GLint getUniformLocation(const char *name);
    
private:
    DISALLOW_COPY_AND_ASSIGN(GLProgram);
    std::vector<ShaderPtr> shaders;
    GLuint programHandle;
    
    void loadShader(GLuint shaderType, const char *path);
};

#endif	/* GLPROGRAM_H */

