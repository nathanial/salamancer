/* 
 * File:   ForwardedFunctionHandler.h
 * Author: nathan
 *
 * Created on October 2, 2014, 7:51 PM
 */

#ifndef FORWARDEDFUNCTIONHANDLER_H
#define	FORWARDEDFUNCTIONHANDLER_H

#include "include/cef_app.h"

#include <memory>
#include <string>

class ForwardedFunctionHandler {
public:
    virtual void Handle(CefRefPtr<CefProcessMessage> message) = 0;
    virtual std::string GetFunctionName() = 0;
};

typedef std::shared_ptr<ForwardedFunctionHandler> ForwardedFunctionHandlerPtr;

#endif	/* FORWARDEDFUNCTIONHANDLER_H */

