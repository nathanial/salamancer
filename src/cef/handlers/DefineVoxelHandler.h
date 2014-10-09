/* 
 * File:   DefineVoxelHandler.h
 * Author: nathan
 *
 * Created on October 8, 2014, 7:23 PM
 */

#ifndef DEFINEVOXELHANDLER_H
#define	DEFINEVOXELHANDLER_H

#include "ForwardedFunctionHandler.h"
#include "../AppContext.h"

class DefineVoxelHandler : public ForwardedFunctionHandler {
private:
    AppContextPtr context;
    
public:
    DefineVoxelHandler(AppContextPtr context) : context(context) {}
    
    virtual void Handle(CefRefPtr<CefProcessMessage> message) OVERRIDE;
    virtual std::string GetFunctionName() OVERRIDE;
};

#endif	/* DEFINEVOXELHANDLER_H */

