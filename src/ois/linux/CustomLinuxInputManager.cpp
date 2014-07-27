/*
The zlib/libpng License

Copyright (c) 2005-2007 Phillip Castaneda (pjcast -- www.wreckedgames.com)

This software is provided 'as-is', without any express or implied warranty. In no event will
the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial 
applications, and to alter it and redistribute it freely, subject to the following
restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that 
		you wrote the original software. If you use this software in a product, 
		an acknowledgment in the product documentation would be appreciated but is 
		not required.

    2. Altered source versions must be plainly marked as such, and must not be 
		misrepresented as being the original software.

    3. This notice may not be removed or altered from any source distribution.
*/
#include "CustomLinuxInputManager.h"
#include "CustomLinuxKeyboard.h"
#include "CustomLinuxMouse.h"
#include "OISException.h"
#include <cstdlib>

#include <cstdlib>
#include <iostream>

using namespace OIS;

//--------------------------------------------------------------------------------//
CustomLinuxInputManager::CustomLinuxInputManager() : InputManager("X11InputManager")
{
	window = 0;

	//Default settings
	grabMouse = true;
	grabKeyboard = true;
	hideMouse = true;
	mGrabs = true;
	useXRepeat = false;
	keyboardUsed = mouseUsed = false;

	//Setup our internal factories
	mFactories.push_back(this);
}

//--------------------------------------------------------------------------------//
CustomLinuxInputManager::~CustomLinuxInputManager()
{
	//Close all joysticks
}

//--------------------------------------------------------------------------------//
void CustomLinuxInputManager::_initialize( ParamList &paramList )
{
	_parseConfigSettings( paramList );

	//Enumerate all devices attached
	_enumerateDevices();
}

//--------------------------------------------------------------------------------//
void CustomLinuxInputManager::_parseConfigSettings( ParamList &paramList )
{
	ParamList::iterator i = paramList.find("WINDOW");
	if( i == paramList.end() ) 
		OIS_EXCEPT( E_InvalidParam, "LinuxInputManager >> No WINDOW!" );

	//TODO 64 bit proof this little conversion xxx wip
	window  = strtoul(i->second.c_str(), 0, 10);

	//--------- Keyboard Settings ------------//
	i = paramList.find("XAutoRepeatOn");
	if( i != paramList.end() )
		if( i->second == "true" )
			useXRepeat = true;

	i = paramList.find("x11_keyboard_grab");
	if( i != paramList.end() )
		if( i->second == "false" )
			grabKeyboard = false;

	//--------- Mouse Settings ------------//
	i = paramList.find("x11_mouse_grab");
	if( i != paramList.end() )
		if( i->second == "false" )
			grabMouse = false;

	i = paramList.find("x11_mouse_hide");
	if( i != paramList.end() )
		if( i->second == "false" )
			hideMouse = false;
}

//--------------------------------------------------------------------------------//
void CustomLinuxInputManager::_enumerateDevices()
{
	//Enumerate all attached devices
	joySticks = unusedJoyStickList.size();
}

//----------------------------------------------------------------------------//
DeviceList CustomLinuxInputManager::freeDeviceList()
{
	DeviceList ret;

	if( keyboardUsed == false )
		ret.insert(std::make_pair(OISKeyboard, mInputSystemName));

	if( mouseUsed == false )
		ret.insert(std::make_pair(OISMouse, mInputSystemName));

	for(JoyStickInfoList::iterator i = unusedJoyStickList.begin(); i != unusedJoyStickList.end(); ++i)
		ret.insert(std::make_pair(OISJoyStick, i->vendor));

	return ret;
}

//----------------------------------------------------------------------------//
int CustomLinuxInputManager::totalDevices(Type iType)
{
	switch(iType)
	{
	case OISKeyboard: return 1;
	case OISMouse: return 1;
	case OISJoyStick: return joySticks;
	default: return 0;
	}
}

//----------------------------------------------------------------------------//
int CustomLinuxInputManager::freeDevices(Type iType)
{
	switch(iType)
	{
	case OISKeyboard: return keyboardUsed ? 0 : 1;
	case OISMouse: return mouseUsed ? 0 : 1;
	case OISJoyStick: return (int)unusedJoyStickList.size();
	default: return 0;
	}
}

//----------------------------------------------------------------------------//
bool CustomLinuxInputManager::vendorExist(Type iType, const std::string & vendor)
{
	if( (iType == OISKeyboard || iType == OISMouse) && vendor == mInputSystemName )
	{
		return true;
	}
	else if( iType == OISJoyStick )
	{
		for(JoyStickInfoList::iterator i = unusedJoyStickList.begin(); i != unusedJoyStickList.end(); ++i)
			if(i->vendor == vendor)
				return true;
	}

	return false;
}

//----------------------------------------------------------------------------//
Object* CustomLinuxInputManager::createObject(InputManager *creator, Type iType, bool bufferMode, const std::string & vendor)
{
	Object *obj = 0;
        
	switch(iType)
	{
	case OISKeyboard:
	{
		if( keyboardUsed == false )
			obj = new CustomLinuxKeyboard(this, bufferMode, grabKeyboard, useXRepeat);
		break;
	}
	case OISMouse:
	{
		if( mouseUsed == false ){
                    obj = new CustomLinuxMouse(this, bufferMode, grabMouse, hideMouse);
                }
		break;
	}
	default:
		break;
	}

	if( obj == 0 )
		OIS_EXCEPT(E_InputDeviceNonExistant, "No devices match requested type.");

	return obj;
}

//----------------------------------------------------------------------------//
void CustomLinuxInputManager::destroyObject( Object* obj )
{
	if( obj )
	{
		delete obj;
	}
}
