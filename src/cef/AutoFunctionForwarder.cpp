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
        if (arguments.size() < this->functionDescription.arguments.size()) {
            exception = "Not enough arguments to function";
        } else {
            CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
            msgArgs->SetString(0, this->functionDescription.name);
            for(int i = 0; i < this->functionDescription.arguments.size(); i++){
                switch(this->functionDescription.arguments[i]){
                    case AFA_BOOL:
                        if(!arguments[i]->IsBool()){
                            exception = "Argument " + std::to_string(i) + " must be a boolean";
                            return true;
                        }
                        msgArgs->SetBool(i+1, arguments[i]->GetBoolValue());
                        break;
                    case AFA_INT:
                        if(!arguments[i]->IsInt()){
                            exception = "Argument " + std::to_string(i) + "  must be an integer";
                            return true;
                        }
                        msgArgs->SetInt(i+1, arguments[i]->GetBoolValue());
                        break;
                    case AFA_STRING:
                        if(!arguments[i]->IsString()){
                            exception = "Argument " + std::to_string(i) + " must be a string";
                            return true;
                        }
                        msgArgs->SetString(i+1, arguments[i]->GetStringValue());
                        break;
                    case AFA_DOUBLE:
                        if(!arguments[i]->IsDouble()){
                            exception = "Argument " + std::to_string(i) + " must be a double";
                            return true;
                        }
                        msgArgs->SetDouble(i+1, arguments[i]->GetDoubleValue());
                        break;
                }
            }
            this->browser->SendProcessMessage(PID_RENDERER, msg);
        }
        return true;
    }
    
    return false;
}
