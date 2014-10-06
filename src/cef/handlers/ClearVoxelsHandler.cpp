/* 
 * File:   ClearVoxelsHandler.cpp
 * Author: nathan
 * 
 * Created on October 5, 2014, 11:59 PM
 */

#include "ClearVoxelsHandler.h"
#include <iostream>

void ClearVoxelsHandler::Handle(CefRefPtr<CefProcessMessage> message) {
    std::cout << "Clear Voxels Handler" << std::endl;
    
    context->world->clearVoxels();
}

std::string ClearVoxelsHandler::GetFunctionName() {
    return "clearVoxels";
}
