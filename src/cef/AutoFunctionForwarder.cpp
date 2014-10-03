/* 
 * File:   AutoFunctionForwarder.cpp
 * Author: nathan
 * 
 * Created on October 2, 2014, 4:13 PM
 */

#include "AutoFunctionForwarder.h"
#include <string>
#include <iostream>

bool AutoFunctionForwarder::Execute(
        const CefString& name, 
        CefRefPtr<CefV8Value> object, 
        const CefV8ValueList& arguments, 
        CefRefPtr<CefV8Value>& retval, 
        CefString& exception)
{
    std::cout << "Auto Function Forwarder " << name.ToString() << std::endl;
    return false;
}
