#ifndef UTIL_H
#define	UTIL_H

#include <string>
#include <vector>
#include <functional>

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
    
    template<typename T, typename F>
    void each(const std::vector<T>& collection, const F & lambda){
        for(auto it = collection.begin(); it != collection.end(); ++it){
            lambda(*it);
        }
    }
};

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(TypeName&) = delete;              \
void operator=(TypeName) = delete;         \
TypeName & operator=(TypeName &&) = delete;


#endif	/* UTIL_H */

