/* 
 * File:   CreateVoxelHandler.cpp
 * Author: nathan
 * 
 * Created on October 2, 2014, 10:35 PM
 */

#include "CreateVoxelHandler.h"
#include <iostream>

void CreateVoxelHandler::Handle(CefRefPtr<CefProcessMessage> message){
    std::cout << "Create Voxel Handler" << std::endl;
    
    auto arguments = message->GetArgumentList();

    int type = arguments->GetInt(1);
    int x = arguments->GetInt(2);
    int y = arguments->GetInt(3);
    int z = arguments->GetInt(4);

    std::cout << "Type: " << type << std::endl;
    std::cout << "X: " << x << std::endl;
    std::cout << "Y: " << y << std::endl;
    std::cout << "Z: " << z << std::endl;
}

std::string CreateVoxelHandler::GetFunctionName(){
    return "createVoxel";
}