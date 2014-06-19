#ifndef UTIL_H
#define	UTIL_H

#include <string>

typedef unsigned int	GLuint;	
typedef unsigned int	GLenum;

namespace util {
    void checkOpenGLError();
    std::string readFile(const char* path);
    void clearOpenGLErrors();
    void checkOpenGLError();
    void checkCompileError(GLuint shader);
    void checkLinkError(GLuint program);
    GLuint compileShader(GLenum shaderType, const char* path);
};

#endif	/* UTIL_H */

