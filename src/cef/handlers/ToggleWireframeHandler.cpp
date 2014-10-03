/* 
 * File:   ToggleWireframeHandler.cpp
 * Author: nathan
 * 
 * Created on October 2, 2014, 7:51 PM
 */

#include "ToggleWireframeHandler.h"

#include <iostream>

void ToggleWireframeHandler::Handle(CefRefPtr<CefProcessMessage> message){
    std::cout << "Toggle Wireframe Handler" << std::endl;
}

std::string ToggleWireframeHandler::GetFunctionName() {
    return "toggleWireframe";
}