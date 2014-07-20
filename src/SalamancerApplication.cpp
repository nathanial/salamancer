#include "SalamancerApplication.h"
#include "framework/terrain/PerlinTerrainGenerator.h"
#include "framework/Position.h"
#include "framework/meshers/MonotoneMesher.h"
#include "framework/meshers/GreedyMesher.h"
#include "framework/World.h"
#include "framework/MeshLoader.h"
#include <functional>
#include "BrowserApp.h"

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
    
    //mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
}

int main(int argc, char *argv[])
{
    // Create application object
//    SalamancerApplication app;
//
//    try {
//        app.go();
//    } catch( Ogre::Exception& e ) {
//        std::cerr << "An exception has occured: " <<
//            e.getFullDescription().c_str() << std::endl;
//    }
    
    CefMainArgs main_args(argc, argv);
    CefRefPtr<BrowserApp> app(new BrowserApp);
    
    int exit_code = CefExecuteProcess(main_args, app.get(), NULL);
    if(exit_code >= 0){
        return exit_code;
    }
    
    CefSettings settings;
    
    CefInitialize(main_args, settings, app.get(), NULL);
    
    CefRunMessageLoop();
    
    CefShutdown();
    
    
    return 0;
}

