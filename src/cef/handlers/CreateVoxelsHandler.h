/* 
 * File:   RunLengthCreateVoxelsHandler.h
 * Author: nathan
 *
 * Created on October 10, 2014, 10:47 PM
 */

#ifndef RUNLENGTHCREATEVOXELSHANDLER_H
#define	RUNLENGTHCREATEVOXELSHANDLER_H

#include "ForwardedFunctionHandler.h"
#include "../AppContext.h"

class CreateVoxelsHandler : public ForwardedFunctionHandler {
private:
    AppContextPtr context;
    
public:
    
    CreateVoxelsHandler(AppContextPtr context) : context(context) {};
    
    virtual void Handle(CefRefPtr<CefProcessMessage> message) OVERRIDE;
    virtual std::string GetFunctionName() OVERRIDE;
};

#endif	/* RUNLENGTHCREATEVOXELSHANDLER_H */

