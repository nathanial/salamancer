/* 
 * File:   CursorHandler.cpp
 * Author: nathan
 * 
 * Created on July 20, 2014, 9:58 PM
 */

#include "CursorHandler.h"

CursorHandler::CursorHandler(MouseCursor *mouseCursor, OIS::Mouse *mouse) 
: mouseCursor(mouseCursor), mouse(mouse) {
}

bool CursorHandler::frameStarted(const FrameEvent& evt){
    this->mouseCursor->updatePosition(this->mouse->getMouseState().X.abs, this->mouse->getMouseState().Y.abs);
    return true;
}