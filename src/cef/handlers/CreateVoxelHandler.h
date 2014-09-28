/* 
 * File:   CreateVoxelHandler.h
 * Author: nathan
 *
 * Created on October 2, 2014, 10:35 PM
 */

#ifndef CREATEVOXELHANDLER_H
#define	CREATEVOXELHANDLER_H

#include "ForwardedFunctionHandler.h"
#include "../AppContext.h"


class CreateVoxelHandler : public ForwardedFunctionHandler {
private:
    AppContextPtr context;
    
public:
   
    CreateVoxelHandler(AppContextPtr context) : context(context) {};
    
    virtual void Handle(CefRefPtr<CefProcessMessage> message) OVERRIDE;
    virtual std::string GetFunctionName() OVERRIDE;
};

#endif	/* CREATEVOXELHANDLER_H */

