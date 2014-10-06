/* 
 * File:   BatchCreateVoxels.h
 * Author: nathan
 *
 * Created on October 6, 2014, 12:28 AM
 */

#ifndef BATCHCREATEVOXELS_H
#define	BATCHCREATEVOXELS_H

#include "assert.h"
#include <algorithm>
#include <string>
#include "include/cef_browser.h"
#include "include/cef_callback.h"
#include "include/cef_frame.h"
#include "include/cef_resource_handler.h"
#include "include/cef_response.h"
#include "include/cef_request.h"
#include "include/cef_scheme.h"

#include "../AppContext.h"

class BatchCreateVoxelsHandler : public CefResourceHandler {

public:

    BatchCreateVoxelsHandler()  {
    }

    virtual bool ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback) OVERRIDE;
    virtual void GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl) OVERRIDE;
    virtual void Cancel() OVERRIDE;
    virtual bool ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback) OVERRIDE;

    IMPLEMENT_REFCOUNTING(BatchCreateVoxelsHandler);
    IMPLEMENT_LOCKING(BatchCreateVoxelsHandler);

private:
    std::string data_;
    std::string mime_type_;
    size_t offset_;

};

class BatchCreateVoxelsHandlerFactory : public CefSchemeHandlerFactory {
public:
    // Return a new scheme handler instance to handle the request.

    virtual CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            const CefString& scheme_name,
            CefRefPtr<CefRequest> request)
    OVERRIDE {
        assert(CefCurrentlyOn(TID_IO));
        return new BatchCreateVoxelsHandler();
    }

    IMPLEMENT_REFCOUNTING(BatchCreateVoxelsHandlerFactory);
};

#endif	/* BATCHCREATEVOXELS_H */

