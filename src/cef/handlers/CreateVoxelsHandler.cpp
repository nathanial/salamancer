/* 
 * File:   RunLengthCreateVoxelsHandler.cpp
 * Author: nathan
 * 
 * Created on October 10, 2014, 10:47 PM
 */

#include "CreateVoxelsHandler.h"
#include <iostream>

void CreateVoxelsHandler::Handle(CefRefPtr<CefProcessMessage> message){
    std::cout << "Run Length Create Voxels Handles" << std::endl;
    
    auto arguments = message->GetArgumentList();
    
    int x = arguments->GetInt(1);
    int y = arguments->GetInt(2);
    int z = arguments->GetInt(3);
    std::string encodedVoxels = arguments->GetString(4);
    
    context->world->createVoxels(x,y,z,encodedVoxels);
}

std::string CreateVoxelsHandler::GetFunctionName() {
    return "createVoxels";
}