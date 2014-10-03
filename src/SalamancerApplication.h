#ifndef __SalamancerApplication_h_
#define __SalamancerApplication_h_

#include "framework/Volume.h"
#include "cef/ClientHandler.h"
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include "ois/linux/CustomLinuxInputManager.h"

#include "cef/App.h"
#include "framework/World.h"


class SalamancerApplication : 
        public Ogre::FrameListener, 
        public Ogre::WindowEventListener, 
        public OIS::KeyListener, 
        public OIS::MouseListener, 
        OgreBites::SdkTrayListener
{
public:
    SalamancerApplication(CefRefPtr<CefApp> cefApp);
    ~SalamancerApplication(void);
    
    void go(void);

private:
    Volume createVolume();
    void createBrowser();

    bool setup();
    bool configure(void);
    void chooseSceneManager(void);
    void createCamera(void);
    void createFrameListener(void);
    void createScene(void);
    void destroyScene(void);
    void createViewports(void);
    void setupResources(void);
    void createResourceListener(void);
    void loadResources(void);

    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) OVERRIDE;

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg ) OVERRIDE;
    virtual bool keyReleased( const OIS::KeyEvent &arg ) OVERRIDE;
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg ) OVERRIDE;
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) OVERRIDE;
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) OVERRIDE;

    // Ogre::WindowEventListener
    //Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw) OVERRIDE;
    //Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw) OVERRIDE;
    
    void toggleHud();
    
    
    CefRefPtr<CefBrowser> browser;
    CefRefPtr<ClientHandler> clientHandler;
    CefRefPtr<CefApp> cefApp;
    
    CefWindowInfo windowInfo;
    CefBrowserSettings browserSettings;
    
    WorldPtr world;
    Ogre::Root *mRoot;
    Ogre::Camera* mCamera;
    Ogre::SceneManager* mSceneMgr;
    Ogre::RenderWindow* mWindow;
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
    Ogre::OverlaySystem *mOverlaySystem;
    // OgreBites
    OgreBites::SdkTrayManager* mTrayMgr;
    OgreBites::SdkCameraMan* mCameraMan;       // basic camera controller
    OgreBites::ParamsPanel* mDetailsPanel;     // sample details panel
    bool mCursorWasVisible;                    // was cursor visible before dialog appeared
    bool mShutDown;

    //OIS Input devices
    OIS::CustomLinuxInputManager* mInputManager;
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;
    
    bool hudVisible = true;
};

#endif // #ifndef __TutorialApplication_h_
