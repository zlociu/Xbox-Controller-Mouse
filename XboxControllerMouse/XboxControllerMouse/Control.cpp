#include "Control.h"

void Control::SendLeftMouseClick(WORD xButton)
{
    if ((gamepad->prevButton & xButton) == 0x0000)
    {
        SendMouse(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, cursorPos);
        SendMouse(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE, cursorPos);
        gamepad->prevButton |= xButton;
    }
}

void Control::SendLeftMouseHold(WORD xButton)
{
    if ((gamepad->prevButton & xButton) == 0x0000)
    {
        SendMouse(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, cursorPos);
        gamepad->prevButton |= xButton;
    }
}

void Control::SendLeftMouseRelease(WORD xButton)
{
    if ((gamepad->prevButton & xButton) == xButton) SendMouse(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE, cursorPos);
}

void Control::SendRightMouseClick(WORD xButton)
{
    if ((gamepad->prevButton & xButton) == 0x0000)
    {
        SendMouse(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_ABSOLUTE, cursorPos);
        SendMouse(MOUSEEVENTF_RIGHTUP | MOUSEEVENTF_ABSOLUTE, cursorPos);
        gamepad->prevButton |= xButton;
    }
}

void Control::SendMiddleMouseClick(WORD xButton)
{
    if ((gamepad->prevButton & xButton) == 0x0000)
    {
        SendMouse(MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_ABSOLUTE, cursorPos);
        SendMouse(MOUSEEVENTF_MIDDLEUP | MOUSEEVENTF_ABSOLUTE, cursorPos);
        gamepad->prevButton |= xButton;
    }
}

void Control::SendMacroKeyboard(WORD xButton, WORD vKey1, WORD vKey2)
{
    if ((gamepad->prevButton & xButton) == 0x0000)
    {
        SendKeyboard(vKey1, 0);
        SendKeyboard(vKey2, 0);
        SendKeyboard(vKey2, KEYEVENTF_KEYUP);
        SendKeyboard(vKey1, KEYEVENTF_KEYUP);
        gamepad->prevButton |= xButton;
    }
}

void Control::SendMacroKeyboard(WORD xButton, WORD vKey1, WORD vKey2, WORD vKey3)
{
    if ((gamepad->prevButton & xButton) == 0x0000)
    {
        SendKeyboard(vKey1, 0);
        SendKeyboard(vKey2, 0);
        SendKeyboard(vKey3, 0);
        SendKeyboard(vKey3, KEYEVENTF_KEYUP);
        SendKeyboard(vKey2, KEYEVENTF_KEYUP);
        SendKeyboard(vKey1, KEYEVENTF_KEYUP);
        gamepad->prevButton |= xButton;
    }
}

void Control::SendOneKey(WORD xButton, WORD vKey)
{
    if ((gamepad->prevButton & xButton) == 0x0000)
    {
        SendKeyboard(vKey, 0);
        SendKeyboard(vKey, KEYEVENTF_KEYUP);
        gamepad->prevButton |= xButton;
    }
}

void Control::SendOneKeyHold(WORD xButton, WORD vKey)
{
    if ((gamepad->prevButton & xButton) == 0x0000)
    {
        SendKeyboard(vKey, 0);
        gamepad->prevButton |= xButton;
    }
}

void Control::SendOneKeyRelease(WORD xButton, WORD vKey)
{
    if ((gamepad->prevButton & xButton) == xButton) SendKeyboard(vKey, KEYEVENTF_KEYUP);
}

void Control::ChangeScrollSpeed(int value = 5)
{
    scrollSpeed = scrollSpeed ^ value;
}

void Control::CursorControlLeft(void)
{
    POINT cursorMove = { 0, 0 };
    if ((abs(gamepad->LeftStickX) - gamepad->deadZoneLeft) > 0)
    {
        cursorMove.x = (abs(gamepad->LeftStickX) >> 12) & 15;
        cursorMove.x = cursorMove.x << 1;
        if (gamepad->LeftTrigger == 1) cursorMove.x = cursorMove.x >> 2;
        if (gamepad->LeftStickX < 0) cursorMove.x *= -1;
    }
    if ((abs(gamepad->LeftStickY) - gamepad->deadZoneLeft) > 0)
    {
        cursorMove.y = (abs(gamepad->LeftStickY) >> 12) & 15;
        cursorMove.y = cursorMove.y << 1;
        if (gamepad->LeftTrigger == 1) cursorMove.y = cursorMove.y >> 2;
        if (gamepad->LeftStickY > 0) cursorMove.y *= -1;
    }

    if (cursorMove != POINT{ 0,0 })
    {
        SendMouse(MOUSEEVENTF_MOVE, cursorMove);
    }
}

void Control::CursorControlRigth()
{
    POINT cursorMove = { 0, 0 };
    if ((abs(gamepad->RightStickX) - gamepad->deadZoneRight) > 0)
    {
        cursorMove.x = (abs(gamepad->RightStickX) >> 12) & 15;
        cursorMove.x = cursorMove.x << 1;
        if (gamepad->RightTrigger == 1) cursorMove.x = cursorMove.x >> 2;
        if (gamepad->RightStickX < 0) cursorMove.x *= -1;
    }
    if ((abs(gamepad->RightStickY) - gamepad->deadZoneRight) > 0)
    {
        cursorMove.y = (abs(gamepad->RightStickY) >> 12) & 15;
        cursorMove.y = cursorMove.y << 1;
        if (gamepad->RightTrigger == 1) cursorMove.y = cursorMove.y >> 2;
        if (gamepad->RightStickY > 0) cursorMove.y *= -1;
    }

    if (cursorMove != POINT{ 0,0 })
    {
        SendMouse(MOUSEEVENTF_MOVE, cursorMove);
    }
}

void Control::ScrollControlLeft()
{
    SHORT mouseWheel = 0;

    if ((abs(gamepad->LeftStickY) - gamepad->deadZoneLeft) > 0)
    {
        mouseWheel = (abs(gamepad->LeftStickY) >> 12) & 15;
        mouseWheel <<= 1;
        if (gamepad->LeftTrigger == 0) mouseWheel <<= scrollSpeed;
        if (gamepad->LeftStickY < 0) mouseWheel *= -1;
    }

    if (mouseWheel != 0)
    {
        SendMouse(MOUSEEVENTF_WHEEL | MOUSEEVENTF_ABSOLUTE, cursorPos, mouseWheel);
    }
}

void Control::ScrollControlRight(void)
{
    SHORT mouseWheel = 0;

    if ((abs(gamepad->RightStickY) - gamepad->deadZoneRight) > 0)
    {
        mouseWheel = (abs(gamepad->RightStickY) >> 12) & 15;
        mouseWheel <<= 1;
        if (gamepad->RightTrigger == 0) mouseWheel <<= scrollSpeed;
        if (gamepad->RightStickY < 0) mouseWheel *= -1;
    }

    if (mouseWheel != 0)
    {
        SendMouse(MOUSEEVENTF_WHEEL | MOUSEEVENTF_ABSOLUTE, cursorPos, mouseWheel);
    }
}

void Control::SendMouse(DWORD dwFlags, POINT curPos, DWORD mouseData)
{
    MOUSEINPUT mi;
    mi.dx = curPos.x;
    mi.dy = curPos.y;
    mi.dwFlags = dwFlags;
    mi.mouseData = mouseData;
    mi.dwExtraInfo = 0;
    mi.time = 0;

    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi = mi;

    SendInput(1, &input, sizeof(INPUT));
}

void Control::SendKeyboard(WORD vKey, DWORD dwFlags)
{
    KEYBDINPUT ki;
    ki.wVk = vKey;
    ki.wScan = 0;
    ki.dwFlags = dwFlags;
    ki.dwExtraInfo = 0;
    ki.time = 0;

    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki = ki;

    SendInput(1, &input, sizeof(INPUT));
}


