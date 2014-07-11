/* 
 * File:   exceptions.h
 * Author: nathan
 *
 * Created on June 19, 2014, 2:41 AM
 */

#ifndef EXCEPTIONS_H
#define	EXCEPTIONS_H

#include <string>
#include <exception>

class FileNotFoundException : public std::exception {
    std::string path; 
    
public:
    FileNotFoundException(std::string path) : path(path) {}
    
    ~FileNotFoundException() throw() {
    }
    
    virtual const char* what() const throw(){
        return std::string("File Not Found: " + path).c_str();
    }
};

class SDLInitFailed : public std::exception {
    virtual const char* what() const throw(){
        return "Could not initialize SDL";
    }
};


class CouldNotInitGlew : public std::exception {
    virtual const char* what() const throw(){
        return "Unable to initialize GLEW";
    }
};

class OpenGLException : public std::exception {
    virtual const char* what() const throw(){
        return "OPENGL ERROR";
    }
};

#endif	/* EXCEPTIONS_H */

