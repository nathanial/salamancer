#ifndef UTIL_H
#define	UTIL_H

#include <string>

typedef unsigned int	GLuint;	

namespace util {
    void checkOpenGLError();
    std::string readFile(const char* path);
    void clearOpenGLErrors();
    void checkOpenGLError();
    void checkCompileError(GLuint shader);
    void checkLinkError(GLuint program);
};

#endif	/* UTIL_H */

