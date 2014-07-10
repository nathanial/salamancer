#include "SalamancerApplication.h"

using namespace Ogre;
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
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
    
    auto ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
    auto headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
    headNode->attachObject(ogreHead);
    auto light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);
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

