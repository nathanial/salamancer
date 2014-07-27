/* 
 * File:   RenderHandler.cpp
 * Author: nathan
 * 
 * Created on July 20, 2014, 1:42 AM
 * 
 * 
 */

#include <iostream>
#include "RenderHandler.h"
#include "include/internal/cef_linux.h"

#include "include/cef_app.h"
#include "include/cef_client.h"

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <X11/Xcursor/Xcursor.h>
#include <X11/keysym.h>
#include <X11/XF86keysym.h>

#include <ctime>

namespace {
    enum CURSORS {
        POINTER = 6,
        DEFAULT = 10,
        TEXT = 14,
        RESIZE_EW = 18,
        RESIZE_NS = 22,
        RESIZE_NE = 26,
        RESIZE_NW = 30,
        RESIZE_SE = 34,
        RESIZE_SW = 38,
        MOVE = 42
    };
}

bool RenderHandler::frameStarted(const Ogre::FrameEvent &evt){
    if(Ogre::Root::getSingletonPtr()->getAutoCreatedWindow()->isClosed()){
        return false;
    }
    
    CefDoMessageLoopWork();
    

    if(this->hasKeyBeenPressed){
        if(this->repeatStarted && this->keyTimer->getMilliseconds() > 10){
            this->browser->GetHost()->SendKeyEvent(this->keyEvent);
            this->keyTimer->reset();
        } else if(this->keyTimer->getMilliseconds() > 500){
            this->repeatStarted = true;
            this->browser->GetHost()->SendKeyEvent(this->keyEvent);
            this->keyTimer->reset();
        } 
    }
    return true;
}

bool RenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect){
    rect = CefRect(0, 0, renderTexture->getWidth(), renderTexture->getHeight());
    return true;
}

void RenderHandler::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height){
    Ogre::HardwarePixelBufferSharedPtr texBuf = renderTexture->getBuffer();
    texBuf->lock(Ogre::HardwareBuffer::HBL_DISCARD);
    memcpy(texBuf->getCurrentLock().data, buffer, width*height*4);
    texBuf->unlock();
}

void RenderHandler::OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor){
    ::Display* xDisplay;
    XID xid;
    this->window->getCustomAttribute("XDISPLAY", &xDisplay);
    this->window->getCustomAttribute("WINDOW", &xid);
    XDefineCursor(xDisplay, xid, cursor);
}

enum KeyboardCode {
  VKEY_BACK = 0x08,
  VKEY_TAB = 0x09,
  VKEY_BACKTAB = 0x0A,
  VKEY_CLEAR = 0x0C,
  VKEY_RETURN = 0x0D,
  VKEY_SHIFT = 0x10,
  VKEY_CONTROL = 0x11,
  VKEY_MENU = 0x12,
  VKEY_PAUSE = 0x13,
  VKEY_CAPITAL = 0x14,
  VKEY_KANA = 0x15,
  VKEY_HANGUL = 0x15,
  VKEY_JUNJA = 0x17,
  VKEY_FINAL = 0x18,
  VKEY_HANJA = 0x19,
  VKEY_KANJI = 0x19,
  VKEY_ESCAPE = 0x1B,
  VKEY_CONVERT = 0x1C,
  VKEY_NONCONVERT = 0x1D,
  VKEY_ACCEPT = 0x1E,
  VKEY_MODECHANGE = 0x1F,
  VKEY_SPACE = 0x20,
  VKEY_PRIOR = 0x21,
  VKEY_NEXT = 0x22,
  VKEY_END = 0x23,
  VKEY_HOME = 0x24,
  VKEY_LEFT = 0x25,
  VKEY_UP = 0x26,
  VKEY_RIGHT = 0x27,
  VKEY_DOWN = 0x28,
  VKEY_SELECT = 0x29,
  VKEY_PRINT = 0x2A,
  VKEY_EXECUTE = 0x2B,
  VKEY_SNAPSHOT = 0x2C,
  VKEY_INSERT = 0x2D,
  VKEY_DELETE = 0x2E,
  VKEY_HELP = 0x2F,
  VKEY_0 = 0x30,
  VKEY_1 = 0x31,
  VKEY_2 = 0x32,
  VKEY_3 = 0x33,
  VKEY_4 = 0x34,
  VKEY_5 = 0x35,
  VKEY_6 = 0x36,
  VKEY_7 = 0x37,
  VKEY_8 = 0x38,
  VKEY_9 = 0x39,
  VKEY_A = 0x41,
  VKEY_B = 0x42,
  VKEY_C = 0x43,
  VKEY_D = 0x44,
  VKEY_E = 0x45,
  VKEY_F = 0x46,
  VKEY_G = 0x47,
  VKEY_H = 0x48,
  VKEY_I = 0x49,
  VKEY_J = 0x4A,
  VKEY_K = 0x4B,
  VKEY_L = 0x4C,
  VKEY_M = 0x4D,
  VKEY_N = 0x4E,
  VKEY_O = 0x4F,
  VKEY_P = 0x50,
  VKEY_Q = 0x51,
  VKEY_R = 0x52,
  VKEY_S = 0x53,
  VKEY_T = 0x54,
  VKEY_U = 0x55,
  VKEY_V = 0x56,
  VKEY_W = 0x57,
  VKEY_X = 0x58,
  VKEY_Y = 0x59,
  VKEY_Z = 0x5A,
  VKEY_LWIN = 0x5B,
  VKEY_COMMAND = VKEY_LWIN,  // Provide the Mac name for convenience.
  VKEY_RWIN = 0x5C,
  VKEY_APPS = 0x5D,
  VKEY_SLEEP = 0x5F,
  VKEY_NUMPAD0 = 0x60,
  VKEY_NUMPAD1 = 0x61,
  VKEY_NUMPAD2 = 0x62,
  VKEY_NUMPAD3 = 0x63,
  VKEY_NUMPAD4 = 0x64,
  VKEY_NUMPAD5 = 0x65,
  VKEY_NUMPAD6 = 0x66,
  VKEY_NUMPAD7 = 0x67,
  VKEY_NUMPAD8 = 0x68,
  VKEY_NUMPAD9 = 0x69,
  VKEY_MULTIPLY = 0x6A,
  VKEY_ADD = 0x6B,
  VKEY_SEPARATOR = 0x6C,
  VKEY_SUBTRACT = 0x6D,
  VKEY_DECIMAL = 0x6E,
  VKEY_DIVIDE = 0x6F,
  VKEY_F1 = 0x70,
  VKEY_F2 = 0x71,
  VKEY_F3 = 0x72,
  VKEY_F4 = 0x73,
  VKEY_F5 = 0x74,
  VKEY_F6 = 0x75,
  VKEY_F7 = 0x76,
  VKEY_F8 = 0x77,
  VKEY_F9 = 0x78,
  VKEY_F10 = 0x79,
  VKEY_F11 = 0x7A,
  VKEY_F12 = 0x7B,
  VKEY_F13 = 0x7C,
  VKEY_F14 = 0x7D,
  VKEY_F15 = 0x7E,
  VKEY_F16 = 0x7F,
  VKEY_F17 = 0x80,
  VKEY_F18 = 0x81,
  VKEY_F19 = 0x82,
  VKEY_F20 = 0x83,
  VKEY_F21 = 0x84,
  VKEY_F22 = 0x85,
  VKEY_F23 = 0x86,
  VKEY_F24 = 0x87,
  VKEY_NUMLOCK = 0x90,
  VKEY_SCROLL = 0x91,
  VKEY_LSHIFT = 0xA0,
  VKEY_RSHIFT = 0xA1,
  VKEY_LCONTROL = 0xA2,
  VKEY_RCONTROL = 0xA3,
  VKEY_LMENU = 0xA4,
  VKEY_RMENU = 0xA5,
  VKEY_BROWSER_BACK = 0xA6,
  VKEY_BROWSER_FORWARD = 0xA7,
  VKEY_BROWSER_REFRESH = 0xA8,
  VKEY_BROWSER_STOP = 0xA9,
  VKEY_BROWSER_SEARCH = 0xAA,
  VKEY_BROWSER_FAVORITES = 0xAB,
  VKEY_BROWSER_HOME = 0xAC,
  VKEY_VOLUME_MUTE = 0xAD,
  VKEY_VOLUME_DOWN = 0xAE,
  VKEY_VOLUME_UP = 0xAF,
  VKEY_MEDIA_NEXT_TRACK = 0xB0,
  VKEY_MEDIA_PREV_TRACK = 0xB1,
  VKEY_MEDIA_STOP = 0xB2,
  VKEY_MEDIA_PLAY_PAUSE = 0xB3,
  VKEY_MEDIA_LAUNCH_MAIL = 0xB4,
  VKEY_MEDIA_LAUNCH_MEDIA_SELECT = 0xB5,
  VKEY_MEDIA_LAUNCH_APP1 = 0xB6,
  VKEY_MEDIA_LAUNCH_APP2 = 0xB7,
  VKEY_OEM_1 = 0xBA,
  VKEY_OEM_PLUS = 0xBB,
  VKEY_OEM_COMMA = 0xBC,
  VKEY_OEM_MINUS = 0xBD,
  VKEY_OEM_PERIOD = 0xBE,
  VKEY_OEM_2 = 0xBF,
  VKEY_OEM_3 = 0xC0,
  VKEY_OEM_4 = 0xDB,
  VKEY_OEM_5 = 0xDC,
  VKEY_OEM_6 = 0xDD,
  VKEY_OEM_7 = 0xDE,
  VKEY_OEM_8 = 0xDF,
  VKEY_OEM_102 = 0xE2,
  VKEY_OEM_103 = 0xE3,  // GTV KEYCODE_MEDIA_REWIND
  VKEY_OEM_104 = 0xE4,  // GTV KEYCODE_MEDIA_FAST_FORWARD
  VKEY_PROCESSKEY = 0xE5,
  VKEY_PACKET = 0xE7,
  VKEY_DBE_SBCSCHAR = 0xF3,
  VKEY_DBE_DBCSCHAR = 0xF4,
  VKEY_ATTN = 0xF6,
  VKEY_CRSEL = 0xF7,
  VKEY_EXSEL = 0xF8,
  VKEY_EREOF = 0xF9,
  VKEY_PLAY = 0xFA,
  VKEY_ZOOM = 0xFB,
  VKEY_NONAME = 0xFC,
  VKEY_PA1 = 0xFD,
  VKEY_OEM_CLEAR = 0xFE,
  VKEY_UNKNOWN = 0,

  // POSIX specific VKEYs. Note that as of Windows SDK 7.1, 0x97-9F, 0xD8-DA,
  // and 0xE8 are unassigned.
  VKEY_WLAN = 0x97,
  VKEY_POWER = 0x98,
  VKEY_BRIGHTNESS_DOWN = 0xD8,
  VKEY_BRIGHTNESS_UP = 0xD9,
  VKEY_KBD_BRIGHTNESS_DOWN = 0xDA,
  VKEY_KBD_BRIGHTNESS_UP = 0xE8,

  // Windows does not have a specific key code for AltGr. We use the unused 0xE1
  // (VK_OEM_AX) code to represent AltGr, matching the behaviour of Firefox on
  // Linux.
  VKEY_ALTGR = 0xE1,
  // Windows does not have a specific key code for Compose. We use the unused
  // 0xE6 (VK_ICO_CLEAR) code to represent Compose.
  VKEY_COMPOSE = 0xE6,
};

KeyboardCode KeyboardCodeFromKeyCode(OIS::KeyCode keycode) {
  switch (keycode) {
    case OIS::KeyCode::KC_BACK:
        return VKEY_BACK;
    case OIS::KeyCode::KC_DELETE:
        return VKEY_DELETE;
    case OIS::KeyCode::KC_TAB:
        return VKEY_TAB;
    case OIS::KeyCode::KC_RETURN:
        return VKEY_RETURN;
    case OIS::KeyCode::KC_SPACE:
        return VKEY_SPACE;
    case OIS::KeyCode::KC_HOME:
        return VKEY_HOME;
    case OIS::KeyCode::KC_END:
        return VKEY_END;
    case OIS::KeyCode::KC_PGUP:
        return VKEY_PRIOR;
    case OIS::KeyCode::KC_PGDOWN:
        return VKEY_NEXT;
    case OIS::KeyCode::KC_LEFT:
        return VKEY_LEFT;
    case OIS::KeyCode::KC_RIGHT:
        return VKEY_RIGHT;
    case OIS::KeyCode::KC_DOWN:
        return VKEY_DOWN;
    case OIS::KeyCode::KC_UP:
        return VKEY_UP;
    case OIS::KeyCode::KC_ESCAPE:
        return VKEY_ESCAPE;
    case OIS::KeyCode::KC_A:
        return VKEY_A;
    case OIS::KeyCode::KC_B:
        return VKEY_B;
    case OIS::KeyCode::KC_C:
        return VKEY_C;
    case OIS::KeyCode::KC_D:
        return VKEY_D;
    case OIS::KeyCode::KC_E:
        return VKEY_E;
    case OIS::KeyCode::KC_F:
        return VKEY_F;
    case OIS::KeyCode::KC_G:
        return VKEY_G;
    case OIS::KeyCode::KC_H:
        return VKEY_H;
    case OIS::KeyCode::KC_I:
        return VKEY_I;
    case OIS::KeyCode::KC_J:
        return VKEY_J;
    case OIS::KeyCode::KC_K:
        return VKEY_K;
    case OIS::KeyCode::KC_L:
        return VKEY_L;
    case OIS::KeyCode::KC_M:
        return VKEY_M;
    case OIS::KeyCode::KC_N:
        return VKEY_N;
    case OIS::KeyCode::KC_O:
        return VKEY_O;
    case OIS::KeyCode::KC_P:
        return VKEY_P;
    case OIS::KeyCode::KC_Q:
        return VKEY_Q;
    case OIS::KeyCode::KC_R:
        return VKEY_R;
    case OIS::KeyCode::KC_S:
        return VKEY_S;
    case OIS::KeyCode::KC_T:
        return VKEY_T;
    case OIS::KeyCode::KC_U:
        return VKEY_U;
    case OIS::KeyCode::KC_V:
        return VKEY_V;
    case OIS::KeyCode::KC_W:
        return VKEY_W;
    case OIS::KeyCode::KC_X:
        return VKEY_X;
    case OIS::KeyCode::KC_Y:
        return VKEY_Y;
    case OIS::KeyCode::KC_Z:
        return VKEY_Z;
    case OIS::KeyCode::KC_0:
        return VKEY_0;
    case OIS::KeyCode::KC_1:
        return VKEY_1;
    case OIS::KeyCode::KC_2:
        return VKEY_2;
    case OIS::KeyCode::KC_3:
        return VKEY_3;
    case OIS::KeyCode::KC_4:
        return VKEY_4;
    case OIS::KeyCode::KC_5:
        return VKEY_5;
    case OIS::KeyCode::KC_6:
        return VKEY_6;
    case OIS::KeyCode::KC_7:
        return VKEY_7;
    case OIS::KeyCode::KC_8:
        return VKEY_8;
    case OIS::KeyCode::KC_9:
        return VKEY_9;
      
    case OIS::KeyCode::KC_MULTIPLY:
        return VKEY_MULTIPLY;
    case OIS::KeyCode::KC_ADD:
        return VKEY_ADD;
    case OIS::KeyCode::KC_SUBTRACT:
        return VKEY_SUBTRACT;
    case OIS::KeyCode::KC_DECIMAL:
        return VKEY_DECIMAL;
    case OIS::KeyCode::KC_DIVIDE:
        return VKEY_DIVIDE;
    case OIS::KeyCode::KC_EQUALS:
        return VKEY_OEM_PLUS;
    case OIS::KeyCode::KC_COMMA:
        return VKEY_OEM_COMMA;
    case OIS::KeyCode::KC_MINUS:
        return VKEY_OEM_MINUS;
    case OIS::KeyCode::KC_PERIOD:
        return VKEY_OEM_PERIOD;
    case OIS::KeyCode::KC_COLON:
    case OIS::KeyCode::KC_SEMICOLON:
        return VKEY_OEM_1;
    case OIS::KeyCode::KC_SLASH:
        return VKEY_OEM_2;
    case OIS::KeyCode::KC_GRAVE:
        return VKEY_OEM_3;
    case OIS::KeyCode::KC_LBRACKET:
        return VKEY_OEM_4;    
    case OIS::KeyCode::KC_BACKSLASH:
        return VKEY_OEM_5;
    case OIS::KeyCode::KC_RBRACKET:
        return VKEY_OEM_6;
    case OIS::KeyCode::KC_APOSTROPHE:
        return VKEY_OEM_7;
    case OIS::KeyCode::KC_LSHIFT:
    case OIS::KeyCode::KC_RSHIFT:
        return VKEY_SHIFT;
    case OIS::KeyCode::KC_LCONTROL:
    case OIS::KeyCode::KC_RCONTROL:
        return VKEY_CONTROL;
    case OIS::KeyCode::KC_LMENU:
    case OIS::KeyCode::KC_RMENU:
        return VKEY_MENU; 
    case OIS::KeyCode::KC_CAPITAL:
        return VKEY_CAPITAL;
    case OIS::KeyCode::KC_NUMLOCK:
        return VKEY_NUMLOCK;
    case OIS::KeyCode::KC_SCROLL:
        return VKEY_SCROLL;
    case OIS::KeyCode::KC_INSERT:
        return VKEY_INSERT;
    case OIS::KeyCode::KC_LWIN:
        return VKEY_LWIN;
    case OIS::KeyCode::KC_RWIN:
        return VKEY_RWIN;
    case OIS::KeyCode::KC_F1:
        return VKEY_F1;
    case OIS::KeyCode::KC_F2:
        return VKEY_F2;
    case OIS::KeyCode::KC_F3:
        return VKEY_F3;
    case OIS::KeyCode::KC_F4:
        return VKEY_F4;
    case OIS::KeyCode::KC_F5:
        return VKEY_F5;
    case OIS::KeyCode::KC_F6:
        return VKEY_F6;
    case OIS::KeyCode::KC_F7:
        return VKEY_F7;
    case OIS::KeyCode::KC_F8:
        return VKEY_F8;
    case OIS::KeyCode::KC_F9:
        return VKEY_F9;
    case OIS::KeyCode::KC_F10:
        return VKEY_F10;
    case OIS::KeyCode::KC_F11:
        return VKEY_F11;
    case OIS::KeyCode::KC_F12:
        return VKEY_F12;
    case OIS::KeyCode::KC_F13:
        return VKEY_F13;
    case OIS::KeyCode::KC_F14:
        return VKEY_F14;
    case OIS::KeyCode::KC_F15:
        return VKEY_F15;
  }
  return VKEY_UNKNOWN;
}


bool RenderHandler::keyPressed( const OIS::KeyEvent &arg ){
    KeyboardCode code = KeyboardCodeFromKeyCode(arg.key);
    keyEvent.native_key_code = arg.key;
    keyEvent.windows_key_code = code;
    
    this->repeatStarted = false;
    this->keyTimer->reset();
    
    keyEvent.type = KEYEVENT_RAWKEYDOWN;
    keyEvent.unmodified_character = arg.text;
    keyEvent.character = arg.text;
    this->browser->GetHost()->SendKeyEvent(keyEvent);
    if(code != VKEY_BACK && code != VKEY_DELETE){
        keyEvent.type = KEYEVENT_CHAR;
        this->browser->GetHost()->SendKeyEvent(keyEvent);
    }
    this->hasKeyBeenPressed = true;
    return true;
}
bool RenderHandler::keyReleased( const OIS::KeyEvent &arg ){
    keyEvent.native_key_code = arg.key;
    keyEvent.windows_key_code = KeyboardCodeFromKeyCode(arg.key);
    keyEvent.type = KEYEVENT_KEYUP;
    keyEvent.unmodified_character = arg.text;
    keyEvent.character = arg.text;
    this->browser->GetHost()->SendKeyEvent(keyEvent);
    this->hasKeyBeenPressed = false;
    return true;
}

bool RenderHandler::mouseMoved( const OIS::MouseEvent &arg ){
    CefMouseEvent mouseEvent;
    mouseEvent.x = arg.state.X.abs;
    mouseEvent.y = arg.state.Y.abs;
    this->browser->GetHost()->SendMouseMoveEvent(mouseEvent, false);
    
    CefDoMessageLoopWork();
    
    return true;
}

bool RenderHandler::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
    CefMouseEvent mouseEvent;
    mouseEvent.x = arg.state.X.abs;
    mouseEvent.y = arg.state.Y.abs;
    CefBrowserHost::MouseButtonType mbt = CefBrowserHost::MouseButtonType::MBT_LEFT;
    if(id == OIS::MouseButtonID::MB_Left){
        mbt = CefBrowserHost::MouseButtonType::MBT_LEFT;
    } else if(id == OIS::MouseButtonID::MB_Right){
        mbt = CefBrowserHost::MouseButtonType::MBT_RIGHT;
    } 
    this->browser->GetHost()->SendMouseClickEvent(mouseEvent, mbt, false, 1);
    
    CefDoMessageLoopWork();
    
    return true;
}

bool RenderHandler::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
    CefMouseEvent mouseEvent;
    mouseEvent.x = arg.state.X.abs;
    mouseEvent.y = arg.state.Y.abs;
    CefBrowserHost::MouseButtonType mbt = CefBrowserHost::MouseButtonType::MBT_LEFT;
    if(id == OIS::MouseButtonID::MB_Left){
        mbt = CefBrowserHost::MouseButtonType::MBT_LEFT;
    } else if(id == OIS::MouseButtonID::MB_Right){
        mbt = CefBrowserHost::MouseButtonType::MBT_RIGHT;
    }
    this->browser->GetHost()->SendMouseClickEvent(mouseEvent, mbt, true, 1);
    
    CefDoMessageLoopWork();
    
    return true;
}
