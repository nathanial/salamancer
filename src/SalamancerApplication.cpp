#include "SalamancerApplication.h"
#include "framework/terrain/PerlinTerrainGenerator.h"
#include "framework/Position.h"
#include "framework/Mesher.h"
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

//-------------------------------------------------------------------------------------
void SalamancerApplication::createScene(void)
{
    createColourCube();
    MaterialPtr material = MaterialManager::getSingleton().create(
      "ColorTest", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    material->getTechnique(0)->getPass(0)->setVertexColourTracking(TVC_AMBIENT);
    
    Entity *thisEntity = mSceneMgr->createEntity("cc", "ColorCube");
    thisEntity->setMaterialName("ColorTest");
    SceneNode* thisSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    thisSceneNode->setPosition(0,0,-100);
    thisSceneNode->attachObject(thisEntity);
    
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);
    
}

void createColourCube(void)
{
    PerlinTerrainGenerator gen;
    VolumePtr volume = gen.generate(Position(1,World::YCHUNKS-1, 1));
    auto verticesAndFaces = Mesher::mesh(volume);
    MeshLoader::loadMesh("ColorCube", verticesAndFaces);
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

