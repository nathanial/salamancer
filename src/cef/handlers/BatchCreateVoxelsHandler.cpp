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

bool BatchCreateVoxelsHandler::ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback) {
    std::cout << "Batch Create Voxels" << std::endl;
    
    CefRefPtr<CefPostData> data = request->GetPostData();
    if(data == nullptr){
        std::cout << "No Voxels Posted" << std::endl;
        callback->Continue();
        return true;
    }
    CefPostData::ElementVector elements;
    data->GetElements(elements);
    
    for(CefRefPtr<CefPostDataElement> element : elements) {
        std::string bytes;
        bytes.resize(element->GetBytesCount());
        element->GetBytes(element->GetBytesCount(), &bytes[0]);
        std::cout << "Bytes: " <<  bytes << std::endl;
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