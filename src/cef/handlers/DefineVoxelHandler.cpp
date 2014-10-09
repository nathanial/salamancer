/* 
 * File:   DefineVoxelHandler.cpp
 * Author: nathan
 * 
 * Created on October 8, 2014, 7:23 PM
 */

#include "DefineVoxelHandler.h"


//defineVoxel(integer, {left: })
//defineVoxel(type, textures)
void DefineVoxelHandler::Handle(CefRefPtr<CefProcessMessage> message){
    std::cout << "Define Voxel Handler" << std::endl;
    
    auto arguments = message->GetArgumentList();
    
    int type = arguments->GetInt(1);
    auto textures = arguments->GetDictionary();
}