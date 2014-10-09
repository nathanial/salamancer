/* 
 * File:   DefineVoxelHandler.cpp
 * Author: nathan
 * 
 * Created on October 8, 2014, 7:23 PM
 */

#include "DefineVoxelHandler.h"
#include <iostream>


//defineVoxel(integer, {left: })
//defineVoxel(type, textures)
void DefineVoxelHandler::Handle(CefRefPtr<CefProcessMessage> message){
    std::cout << "Define Voxel Handler" << std::endl;
    
    auto arguments = message->GetArgumentList();
    
    auto name = arguments->GetString(1);
    auto topImage = arguments->GetString(2);
    auto sideImage = arguments->GetString(3);
    auto bottomImage = arguments->GetString(4);
    auto transparent = arguments->GetBool(5);
    
    VoxelDefinition definition;
    definition.name = name;
    definition.topImage = topImage;
    definition.bottomImage = bottomImage;
    definition.sideImage = sideImage;
    definition.transparent = transparent;
    
    this->context->world->defineVoxel(definition);
    
}

std::string DefineVoxelHandler::GetFunctionName() {
    return "defineVoxel";
}