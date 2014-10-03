/* 
 * File:   ToggleWireframeHandler.h
 * Author: nathan
 *
 * Created on October 2, 2014, 7:51 PM
 */

#ifndef TOGGLEWIREFRAMEHANDLER_H
#define	TOGGLEWIREFRAMEHANDLER_H

#include "ForwardedFunctionHandler.h"
#include "../AppContext.h"

class ToggleWireframeHandler : public ForwardedFunctionHandler {
private: 
    AppContextPtr context;
    
public:
    
    ToggleWireframeHandler(AppContextPtr context) : context(context) {}
    
    virtual void Handle(CefRefPtr<CefProcessMessage> message) OVERRIDE;
    virtual std::string GetFunctionName() OVERRIDE;
};

#endif	/* TOGGLEWIREFRAMEHANDLER_H */