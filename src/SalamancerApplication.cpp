#include "SalamancerApplication.h"
#include "framework/terrain/PerlinTerrainGenerator.h"
#include "framework/Position.h"
#include "framework/meshers/GreedyMesher.h"
#include "framework/World.h"
#include "framework/MeshLoader.h"
#include <functional>
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"
#include "cef/BrowserClient.h"
#include "cef/RenderHandler.h"

#include <OIS/OIS.h>

#include <X11/Xcursor/Xcursor.h>
#include <X11/keysym.h>
#include <X11/XF86keysym.h>

#include "ois/linux/LinuxInputManager.h"


using namespace Ogre;

void createColourCube(void);

//-------------------------------------------------------------------------------------
SalamancerApplication::SalamancerApplication(void) 
    : mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mTrayMgr(0),
    mCameraMan(0),
    mDetailsPanel(0),
    mCursorWasVisible(false),
    mShutDown(false),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0)
{
}
//-------------------------------------------------------------------------------------
SalamancerApplication::~SalamancerApplication(void)
{
    if (mTrayMgr) delete mTrayMgr;
    if (mCameraMan) delete mCameraMan;

    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
}

//---------SalamancerApplication----------------------------------------------------------------------------
void SalamancerApplication::createScene(void)
{
    PerlinTerrainGenerator gen;
    
    for(int x = 0; x < World::XCHUNKS; x++){
        for(int y = 0; y < World::YCHUNKS; y++){
            for(int z = 0; z < World::ZCHUNKS; z++){
                VolumePtr volume = gen.generate(Position(x, y, z));
                GreedyMesher mesher;
                VerticesAndFaces vf = mesher.mesh(volume);

                ManualObject* manual = mSceneMgr->createManualObject("cc"+std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z));
                MeshLoader::loadMesh(manual, vf);

                SceneNode* thisSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
                thisSceneNode->setPosition(x * Volume::XWIDTH,y * Volume::YWIDTH,z * Volume::ZWIDTH - 100);
                thisSceneNode->attachObject(manual);
            }
        }
    }
    //mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
}

void SalamancerApplication::createBrowser(){
    Ogre::TexturePtr renderTexture = Ogre::TextureManager::getSingleton().createManual(
                "texture",
                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                Ogre::TEX_TYPE_2D, mWindow->getWidth(), mWindow->getHeight(), 0, Ogre::PF_A8R8G8B8, Ogre::TU_DYNAMIC_WRITE_ONLY);

    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingletonPtr()->create("BrowserMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    material->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_CLOCKWISE); // print both sides of the polygones
    material->getTechnique(0)->getPass(0)->createTextureUnitState("texture");
    material->getTechnique(0)->getPass(0)->setSceneBlending(SBT_TRANSPARENT_ALPHA);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    
    Ogre::Overlay *overlay = Ogre::OverlayManager::getSingletonPtr()->create("BrowserOverlay");
    Ogre::OverlayContainer* panel = static_cast<OverlayContainer*>(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "BrowserPanel"));
    
    panel->setPosition(0.0, 0.0);
    panel->setDimensions(1.0, 1.0);
    panel->setMaterialName("BrowserMaterial");
    overlay->add2D(panel);
    
    overlay->show();
    
    this->renderHandler = new RenderHandler(renderTexture, this->mRoot->getAutoCreatedWindow(), mMouse);
    
    this->windowInfo.SetAsWindowless(0, true);
    
    this->browserClient = new BrowserClient(renderHandler);
    
    this->browser = CefBrowserHost::CreateBrowserSync(windowInfo, browserClient.get(),
            "file:///home/nathan/Projects/salamancer/dist/bin/hud/index.html",
            browserSettings, 
            NULL);
    
    this->renderHandler->SetBrowser(this->browser);
    
    mRoot->addFrameListener(renderHandler);
    
}

int main(int argc, char *argv[])
{
    
    CefMainArgs args(argc, argv);

    int result = CefExecuteProcess(args, nullptr, nullptr);
    // checkout CefApp, derive it and set it as second parameter, for more control on
    // command args and resources.
    if (result >= 0) // child proccess has endend, so exit.
    {
        return result;
    }

    CefSettings settings;
    result = CefInitialize(args, settings, nullptr, nullptr);
    if (!result)
    {
        return -1;
    }
    
    // Create application object
    SalamancerApplication app;

    try {
        app.go();
    } catch( Ogre::Exception& e ) {
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
    }
    
    CefShutdown();
    

    
    return 0;
}


//-------------------------------------------------------------------------------------
bool SalamancerApplication::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog()){
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "TutorialApplication Render Window");
        return true;
    } else {
        return false;
    }
//
//    mWindow = mRoot->initialise(true, "TutorialApplication Render Window");
//    return true;
}

//-------------------------------------------------------------------------------------
void SalamancerApplication::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
    mOverlaySystem = new Ogre::OverlaySystem();
    mSceneMgr->addRenderQueueListener(mOverlaySystem);
}
//-------------------------------------------------------------------------------------
void SalamancerApplication::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0,0,80));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}
//-------------------------------------------------------------------------------------
void SalamancerApplication::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
//    pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
//    pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
    
    mInputManager = new OIS::LinuxInputManager();
    mInputManager->_initialize(pl);

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
    
    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    OgreBites::InputContext inputContext;
    inputContext.mMouse = mMouse; 
    inputContext.mKeyboard = mKeyboard;
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, inputContext, this);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMRIGHT);
    mTrayMgr->hideCursor();

    // create a params panel for displaying sample details
    Ogre::StringVector items;
    items.push_back("cam.pX");
    items.push_back("cam.pY");
    items.push_back("cam.pZ");
    items.push_back("");
    items.push_back("cam.oW");
    items.push_back("cam.oX");
    items.push_back("cam.oY");
    items.push_back("cam.oZ");
    items.push_back("");
    items.push_back("Filtering");
    items.push_back("Poly Mode");

    mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(9, "Bilinear");
    mDetailsPanel->setParamValue(10, "Solid");
    mDetailsPanel->hide();

    mRoot->addFrameListener(this);
    
    this->createBrowser();

    Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_NONE);
    Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(1);
    
    RenderWindow* window = mRoot->getAutoCreatedWindow();
    std::cout << "Window Name: " << window->getName() << std::endl;
}
//-------------------------------------------------------------------------------------
void SalamancerApplication::destroyScene(void)
{
}
//-------------------------------------------------------------------------------------
void SalamancerApplication::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}
//-------------------------------------------------------------------------------------
void SalamancerApplication::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//-------------------------------------------------------------------------------------
void SalamancerApplication::createResourceListener(void)
{

}
//-------------------------------------------------------------------------------------
void SalamancerApplication::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//-------------------------------------------------------------------------------------
void SalamancerApplication::go(void)
{
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif

    if (!setup())
        return;

    mRoot->startRendering();

    // clean up
    destroyScene();
}
//-------------------------------------------------------------------------------------
bool SalamancerApplication::setup(void)
{
    mRoot = new Ogre::Root(mPluginsCfg);

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    loadResources();

    // Create the scene
    createScene();

    createFrameListener();

    return true;
};
//-------------------------------------------------------------------------------------
bool SalamancerApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------
bool SalamancerApplication::keyPressed( const OIS::KeyEvent &arg )
{
    if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up
    if(arg.key == OIS::KC_ESCAPE){
        mShutDown = true;
    } else if(arg.key == OIS::KC_LMENU || arg.key == OIS::KC_RMENU){
        this->toggleHud();
        return true;
    } else if(this->browser != 0 && this->renderHandler != 0 && this->hudVisible) {
        return this->renderHandler->keyPressed(arg);
    } else {
        this->mCameraMan->injectKeyDown(arg);
    }
    return true;
}

bool SalamancerApplication::keyReleased( const OIS::KeyEvent &arg )
{
    if(this->browser != 0 && this->renderHandler != 0 && this->hudVisible){
        return this->renderHandler->keyReleased(arg);
    } else {
        this->mCameraMan->injectKeyUp(arg);
    }
    return true;
}

bool SalamancerApplication::mouseMoved( const OIS::MouseEvent &arg )
{
    if(this->browser != 0 && this->renderHandler != 0 && this->hudVisible){
        this->renderHandler->mouseMoved(arg);
    } else {
        this->mCameraMan->injectMouseMove(arg);
    }
    return true;
}

bool SalamancerApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if(this->browser != 0 && this->renderHandler != 0  && this->hudVisible){
        return this->renderHandler->mousePressed(arg, id);
    } else {
        this->mCameraMan->injectMouseDown(arg, id);
    }
    
    return true;
}

bool SalamancerApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if(this->browser != 0 && this->renderHandler != 0 && this->hudVisible){
        return this->renderHandler->mouseReleased(arg, id);
    } else {
        this->mCameraMan->injectMouseUp(arg, id);
    }
    return true;
}

//Adjust mouse clipping area
void SalamancerApplication::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void SalamancerApplication::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}

void SalamancerApplication::toggleHud(){
    ::Display* display;
    XID window;
    Ogre::RenderWindow *renderWindow = this->mRoot->getAutoCreatedWindow();
    renderWindow->getCustomAttribute("XDISPLAY", &display);
    renderWindow->getCustomAttribute("WINDOW", &window);
    
    if(hudVisible){
        hudVisible = false;
        XGrabPointer(display, window, true, 0, true, true, window, 0L, 0L);
        
        Pixmap bm_no;
	XColor black, dummy;
	Colormap colormap;
	static char no_data[] = { 0,0,0,0,0,0,0,0 };

	colormap = DefaultColormap( display, DefaultScreen(display) );
	XAllocNamedColor( display, colormap, "black", &black, &dummy );
	bm_no = XCreateBitmapFromData( display, window, no_data, 8, 8 );
	Cursor cursor = XCreatePixmapCursor( display, bm_no, bm_no, &black, &black, 0, 0 );
        
        XDefineCursor(display, window, cursor);
    } else {
        hudVisible = true;                
        XUngrabPointer(display, 0L);
        XUndefineCursor(display, window);
    }
}