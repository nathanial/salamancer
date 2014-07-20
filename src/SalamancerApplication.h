#ifndef __SalamancerApplication_h_
#define __SalamancerApplication_h_

#include "BaseApplication.h"
#include "framework/Volume.h"
#include "cef/BrowserClient.h"
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"

class SalamancerApplication : public BaseApplication
{
public:
    SalamancerApplication(void);
    virtual ~SalamancerApplication(void);

protected:
    virtual void createScene(void);
    
private:
    Volume createVolume();
    
    void createBrowser();
    
    CefRefPtr<CefBrowser> browser;
    CefRefPtr<BrowserClient> browserClient;
    
    CefWindowInfo windowInfo;
    CefBrowserSettings browserSettings;
        
};

#endif // #ifndef __TutorialApplication_h_
