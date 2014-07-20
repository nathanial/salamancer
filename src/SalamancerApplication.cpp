#include "SalamancerApplication.h"
#include "framework/terrain/PerlinTerrainGenerator.h"
#include "framework/Position.h"
#include "framework/meshers/MonotoneMesher.h"
#include "framework/meshers/GreedyMesher.h"
#include "framework/World.h"
#include "framework/MeshLoader.h"
#include <functional>
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"
#include "cef/BrowserClient.h"
#include "cef/RenderHandler.h"

using namespace Ogre;

void createColourCube(void);

//-------------------------------------------------------------------------------------
SalamancerApplication::SalamancerApplication(void)
{
}
//-------------------------------------------------------------------------------------
SalamancerApplication::~SalamancerApplication(void)
{
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
    this->createBrowser();
    
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
}

void SalamancerApplication::createBrowser(){
    Ogre::TexturePtr renderTexture = Ogre::TextureManager::getSingleton().createManual(
                "texture",
                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                Ogre::TEX_TYPE_2D, 1024, 768, 0, Ogre::PF_A8R8G8B8, Ogre::TU_DYNAMIC_WRITE_ONLY);

    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingletonPtr()->create("material", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    material->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE); // print both sides of the polygones
    material->getTechnique(0)->getPass(0)->createTextureUnitState("texture");
    
    Ogre::MeshPtr mesh = Ogre::MeshManager::getSingletonPtr()->createPlane("mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                                                                 Ogre::Plane(Ogre::Vector3::UNIT_Z, 0), 3, 2);
    Ogre::Entity* entity = mSceneMgr->createEntity(mesh);
    entity->setMaterial(material);

    Ogre::SceneNode *renderNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("node", Ogre::Vector3(0., 0., -3.));

    renderNode->attachObject(entity);

    RenderHandler *renderHandler = new RenderHandler(renderTexture, renderNode);
    
    
    this->windowInfo.SetAsWindowless(0, false);
    
    this->browserClient = new BrowserClient(renderHandler);
    
    this->browser = CefBrowserHost::CreateBrowserSync(windowInfo, browserClient.get(), "http://www.google.com", browserSettings, NULL);
    
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

