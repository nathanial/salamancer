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
    if (name == this->functionDescription.name) {
        std::cout << "Auto Function Forwarder " << name.ToString() << std::endl;
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create("autoForward");
        if (arguments.size() != 1 || !arguments.at(0)->IsBool()) {
            exception = "Invalid arguments to function";
        } else {
            msg->GetArgumentList()->SetString(0, this->functionDescription.name);
            msg->GetArgumentList()->SetBool(1, arguments.at(0)->GetBoolValue());
            this->browser->SendProcessMessage(PID_RENDERER, msg);
        }
        return true;
    }
    
    return false;
}
