/* 
 * File:   BatchCreateVoxels.cpp
 * Author: nathan
 * 
 * Created on October 6, 2014, 12:28 AM
 */

#include "BatchCreateVoxelsHandler.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

bool BatchCreateVoxelsHandler::ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback) {
    std::cout << "Batch Create Voxels" << std::endl;
    
    assert(CefCurrentlyOn(TID_RENDERER));
    
    
    CefRefPtr<CefPostData> data = request->GetPostData();
    if(data == nullptr){
        std::cout << "No Voxels Posted" << std::endl;
        callback->Continue();
        return true;
    }
    CefPostData::ElementVector elements;
    data->GetElements(elements);
    
    for(CefRefPtr<CefPostDataElement> element : elements) {
        std::vector<unsigned char> bytes;
        bytes.resize(element->GetBytesCount());
        element->GetBytes(element->GetBytesCount(), &bytes[0]);
        for(int i = 0; i < bytes.size(); i++){
            if(bytes[i] != 0){
                std::cout << "Got One: " << std::to_string(bytes[i]) << " at: " << i << std::endl;
            }
        }
        
        uint32 x = bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24);
        uint32 y = bytes[4] + (bytes[5] << 8) + (bytes[6] << 16) + (bytes[7] << 24);
        uint32 z = bytes[8] + (bytes[9] << 8) + (bytes[10] << 16) + (bytes[11] << 24);
        
        std::vector<unsigned char> voxels;
        voxels.resize(bytes.size() - 12);
        std::copy(bytes.begin()+12, bytes.end(), voxels.begin());
        this->context->world->batchCreateVoxels(x, y, z, voxels);
    }
    
    callback->Continue();
    
    

    return true;
}

void BatchCreateVoxelsHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl) {
    
}

void BatchCreateVoxelsHandler::Cancel() {
    
}

bool BatchCreateVoxelsHandler::ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback) {
    
}