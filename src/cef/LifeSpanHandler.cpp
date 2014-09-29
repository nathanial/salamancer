
#include "LifeSpanHandler.h"
#include "include/wrapper/cef_message_router.h"

#include "functions/ToggleWireframeHandler.h"

LifeSpanHandler::LifeSpanHandler()
{
    _toggleWireframeHandler = new API::ToggleWireframeHandler();
}

void LifeSpanHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    // Create the browser-side router for query handling.
    CefMessageRouterConfig config;
    _messageRouter = CefMessageRouterBrowserSide::Create(config);
    
    _messageRouter->AddHandler(_toggleWireframeHandler, false);
}