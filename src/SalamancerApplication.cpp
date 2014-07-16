#include "SalamancerApplication.h"
#include "framework/terrain/PerlinTerrainGenerator.h"
#include "framework/Position.h"
#include "framework/meshers/MonotoneMesher.h"
#include "framework/meshers/GreedyMesher.h"
#include "framework/World.h"
#include "framework/MeshLoader.h"
#include <functional>

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
//    MaterialPtr material = MaterialManager::getSingleton().create(
//      "red", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//    material->getTechnique(0)->getPass(0)->setVertexColourTracking(TVC_AMBIENT);
    
    PerlinTerrainGenerator gen;
    
    for(int x = 0; x < 1; x++){
        for(int z = 0; z < 1; z++){
            VolumePtr volume = gen.generate(Position(x, World::YCHUNKS-2, z));
            GreedyMesher mesher;
            Quads quads = mesher.mesh(volume);
            
            ManualObject* manual = mSceneMgr->createManualObject("cc"+std::to_string(x) + ","+ std::to_string(z));
            MeshLoader::loadMesh(manual, quads);
            
            SceneNode* thisSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
            thisSceneNode->setPosition(x * 16,0,z * 16 - 100);
            thisSceneNode->attachObject(manual);
        }
    }
    
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
//    Ogre::Light* light = mSceneMgr->createLight("MainLight");
//    light->setPosition(20.0f, 80.0f, 50.0f);
    
}

void createColourCube(void)
{
    PerlinTerrainGenerator gen;
    for(int x = 0; x < World::XCHUNKS; x++){
        for(int z = 0; z < World::ZCHUNKS; z++){
            VolumePtr volume = gen.generate(Position(x,World::YCHUNKS-1, z));
            MonotoneMesher mesher;
            auto verticesAndFaces = mesher.mesh(volume);
            MeshLoader::loadMesh("ColorCube"+std::to_string(x)+","+std::to_string(z), verticesAndFaces);
        }
    }
}


int main(int argc, char *argv[])
{
    // Create application object
    SalamancerApplication app;

    try {
        app.go();
    } catch( Ogre::Exception& e ) {
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
    }
    return 0;
}

