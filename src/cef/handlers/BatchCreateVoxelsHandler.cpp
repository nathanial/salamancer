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

namespace {
    class BatchCreateVoxelsTask : public CefTask {
    public:
        int x, y, z;
        std::vector<unsigned char> voxels;
        AppContextPtr context;
        
        BatchCreateVoxelsTask(AppContextPtr context, int x, int y, int z, std::vector<unsigned char> voxels)
        : context(context), x(x), y(y), z(z), voxels(voxels)
        {
        }
        
        virtual void Execute() OVERRIDE {
            this->context->world->batchCreateVoxels(x, y, z, voxels);
        }
        
        IMPLEMENT_REFCOUNTING(BatchCreateVoxelsTask);
    };
    
}

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
        std::vector<unsigned char> bytes;
        bytes.resize(element->GetBytesCount());
        element->GetBytes(element->GetBytesCount(), &bytes[0]);
        unsigned char x = bytes[0];
        unsigned char y = bytes[1];
        unsigned char z = bytes[2];
        std::vector<unsigned char> voxels;
        voxels.resize(bytes.size() - 3);
        std::copy(bytes.begin()+3, bytes.end(), voxels.begin());

        if(!CefPostTask(TID_UI, new BatchCreateVoxelsTask(this->context, x, y, z, voxels))){
            throw std::runtime_error("Could not post task");
        }
        //CefPostTask(TID_IO, NewCefRunnableFunction(MyFunction, param1, param2));
        
        //this->browser->SendProcessMessage(PID_RENDERER, CefProcessMessage::Create("batchCreateVoxels"));
        //this->context->world->batchCreateVoxels(x, y, z, voxels);
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