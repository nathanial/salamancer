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
}

std::string CreateVoxelHandler::GetFunctionName(){
    return "createVoxel";
}