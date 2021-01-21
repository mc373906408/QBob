#include "WindowHook.h"
#include <QCursor>

#include "ScreenCapture/ScreenCapture.h"
#include "Tools/Tools.h"


bool WindowHook::mouseMoveEvent(QHookMouseEvent *event)
{

    return true;
}

bool WindowHook::mousePressEvent(QHookMouseEvent *event)
{
    return true;
}

bool WindowHook::mouseReleaseEvent(QHookMouseEvent *event)
{
    return true;
}

bool WindowHook::keyPressEvent(QHookKeyEvent *event)
{
    /*键盘按下*/
    /*Ctrl*/
    if(event->keyCode()==162||event->keyCode()==163){
        isCtrl=true;
    }
    /*Win*/
    if(event->keyCode()==91){
        isWin=true;
    }
    /*Shift*/
    if(event->keyCode()==160||event->keyCode()==161){
        isShift=true;
    }
    return true;
}

bool WindowHook::keyReleaseEvent(QHookKeyEvent *event)
{
    /*键盘抬起*/
    /*Ctrl*/
    if(event->keyCode()==162||event->keyCode()==163){
        isCtrl=false;
    }
    /*Win*/
    if(event->keyCode()==91){
        isWin=false;
    }
    /*Shift*/
    if(event->keyCode()==160||event->keyCode()==161){
        isShift=false;
    }
    /*Alt+a*/
    if(event->isAlt()&&event->keyCode()==65){
        int id=Tools::getInstance().getMouseDesktopInt(QCursor::pos());
        ScreenCapture::getInstance().startScreenshot(id);
    }

    /*Esc*/
    if(event->keyCode()==27){
        ScreenCapture::getInstance().stopScreenshot();
    }

    return true;
}


WindowHook::WindowHook()
{
    m_hook=QHook::instance();
    m_hook->hookMouse();
    m_hook->hookKeyboard();
}
