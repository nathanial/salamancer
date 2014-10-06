/* 
 * File:   ClearVoxelsHandler.h
 * Author: nathan
 *
 * Created on October 5, 2014, 11:59 PM
 */

#ifndef CLEARVOXELSHANDLER_H
#define	CLEARVOXELSHANDLER_H

#include "ForwardedFunctionHandler.h"
#include "../AppContext.h"

class ClearVoxelsHandler : public ForwardedFunctionHandler {
private:
    AppContextPtr context;
    
public:
    
    ClearVoxelsHandler(AppContextPtr context) : context(context) { }
    
    virtual void Handle(CefRefPtr<CefProcessMessage> message) OVERRIDE;
    virtual std::string GetFunctionName() OVERRIDE;

};

#endif	/* CLEARVOXELSHANDLER_H */

