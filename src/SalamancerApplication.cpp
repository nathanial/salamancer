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
    createColourCube();
    MaterialPtr material = MaterialManager::getSingleton().create(
      "ColorTest", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    material->getTechnique(0)->getPass(0)->setVertexColourTracking(TVC_AMBIENT);
    
    for(int x = 0; x < World::XCHUNKS; x++){
        for(int z = 0; z < World::ZCHUNKS; z++){
            Entity *thisEntity = mSceneMgr->createEntity(
                    "cc"+std::to_string(x) + ","+ std::to_string(z), 
                    "ColorCube" + std::to_string(x) + "," + std::to_string(z)
                    );
            thisEntity->setMaterialName("ColorTest");
            SceneNode* thisSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
            thisSceneNode->setPosition(x * 16,0,z * 16 - 100);
            thisSceneNode->attachObject(thisEntity);
        }
    }
    
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);
    
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

