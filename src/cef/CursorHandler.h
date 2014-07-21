/* 
 * File:   CursorHandler.h
 * Author: nathan
 *
 * Created on July 20, 2014, 9:58 PM
 */

#ifndef CURSORHANDLER_H
#define	CURSORHANDLER_H

#include <OGRE/OgreEntity.h>
#include <OGRE/OgreHardwarePixelBuffer.h>
#include <OGRE/OgreMeshManager.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreRoot.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "MouseCursor.h"

class CursorHandler : public Ogre::FrameListener {
    
    public:
        CursorHandler(MouseCursor *mouseCursor, OIS::Mouse *mouse);
        
        bool frameStarted(const FrameEvent& evt);
    
    private:
        MouseCursor* mouseCursor;
        OIS::Mouse* mouse;
};

#endif	/* CURSORHANDLER_H */

