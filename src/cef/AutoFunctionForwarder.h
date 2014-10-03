/* 
 * File:   AutoFunctionForwarder.h
 * Author: nathan
 *
 * Created on October 2, 2014, 4:13 PM
 */

#ifndef AUTOFUNCTIONFORWARDER_H
#define	AUTOFUNCTIONFORWARDER_H

#include "include/cef_v8.h"

#include <string>
#include <vector>

enum AutoFunctionArg {
    AFA_BOOL,
    AFA_INT,
    AFA_STRING,
    AFA_DOUBLE
};

class AutoFunctionDescription {
public:
    std::string name;
    std::vector<AutoFunctionArg> arguments;
};

class AutoFunctionForwarder : public CefV8Handler {
private: 
    CefRefPtr<CefBrowser> browser;
    CefRefPtr<CefFrame> frame;
    AutoFunctionDescription functionDescription;
    
    void CreateAutoFunction(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context, AutoFunctionDescription description);
    
public:
    
    AutoFunctionForwarder(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, AutoFunctionDescription functionDescription) 
    : browser(browser), frame(frame), functionDescription(functionDescription) 
    {
    }

    virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
    
    IMPLEMENT_REFCOUNTING(AutoFunctionForwarder);
};

#endif	/* AUTOFUNCTIONFORWARDER_H */

