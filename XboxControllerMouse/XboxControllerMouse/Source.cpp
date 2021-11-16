#include <cstdlib>
#include <cstdio>
#include <Windows.h>
#include "Gamepad.h"

POINT cursorPos;
SHORT scrollSpeed;

POINT operator+(POINT one, POINT second)
{
    POINT result = { one.x + second.x, one.y + second.y };
    return result;
}

bool operator==(POINT one, POINT second)
{
    return (one.x == second.x && one.y == second.y);
}

bool operator!=(POINT one, POINT second)
{
    return (one.x != second.x || one.y != second.y);
}

void SendMouse(DWORD dwFlags, POINT curPos, DWORD mouseData = 0)
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

void SendKeyboard(WORD vKey, DWORD dwFlags)
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

void MouseControl(Gamepad* gp)
{
    //buttons
    GetCursorPos(&cursorPos);
    //HWND currentWindow = WindowFromPoint(cursorPos);
    
    switch (gp->Button)
    {
        case XINPUT_GAMEPAD_A: 
        {
            if ((gp->prevButton & XINPUT_GAMEPAD_A) == 0x0000)
            {
                //SendMessage(currentWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
                SendMouse(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, cursorPos);
                gp->prevButton |= XINPUT_GAMEPAD_A;
            } 
        } break;
        case XINPUT_GAMEPAD_B:
        {
            if ((gp->prevButton & XINPUT_GAMEPAD_B) == 0x0000)
            {
                //SendMessage(currentWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
                SendMouse(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_ABSOLUTE, cursorPos);
                SendMouse(MOUSEEVENTF_RIGHTUP | MOUSEEVENTF_ABSOLUTE, cursorPos);
                gp->prevButton |= XINPUT_GAMEPAD_B;
            }
            
        } break;
        case XINPUT_GAMEPAD_X: break;
        case XINPUT_GAMEPAD_Y:
        {
            if ((gp->prevButton & XINPUT_GAMEPAD_Y) == 0x0000)
            {
                SendKeyboard(VK_ESCAPE, 0);
                SendKeyboard(VK_ESCAPE, KEYEVENTF_KEYUP);
                gp->prevButton |= XINPUT_GAMEPAD_Y;
            }
        } break;
        case XINPUT_GAMEPAD_START:
        {
            if ((gp->prevButton & XINPUT_GAMEPAD_START) == 0x0000)
            {
                SendKeyboard(VK_LWIN, 0);
                SendKeyboard(VK_LWIN, KEYEVENTF_KEYUP);
                gp->prevButton |= XINPUT_GAMEPAD_START;
            }
        } break;
        case XINPUT_GAMEPAD_BACK: break;
        case XINPUT_GAMEPAD_LEFT_THUMB:
        {
            if ((gp->prevButton & XINPUT_GAMEPAD_LEFT_THUMB) == 0x0000)
            {
                SendKeyboard(VK_CONTROL, 0);
                SendKeyboard(0x43, 0);
                SendKeyboard(0x43, KEYEVENTF_KEYUP);
                SendKeyboard(VK_CONTROL, KEYEVENTF_KEYUP);
                gp->prevButton |= XINPUT_GAMEPAD_LEFT_THUMB;
            }
        } break;
        case XINPUT_GAMEPAD_RIGHT_THUMB:
        {
            scrollSpeed = scrollSpeed ^ 5;
        } break;
        case XINPUT_GAMEPAD_LEFT_SHOULDER:
        {
            if ((gp->prevButton & XINPUT_GAMEPAD_LEFT_SHOULDER) == 0x0000)
            {
                SendKeyboard(VK_BACK, 0);
                SendKeyboard(VK_BACK, KEYEVENTF_KEYUP);
                gp->prevButton |= XINPUT_GAMEPAD_LEFT_SHOULDER;
            }
        } break;
        case XINPUT_GAMEPAD_RIGHT_SHOULDER:
        {
            if ((gp->prevButton & XINPUT_GAMEPAD_RIGHT_SHOULDER) == 0x0000)
            {
                SendKeyboard(VK_SHIFT, 0);
                SendKeyboard(VK_BACK, 0);
                SendKeyboard(VK_BACK, KEYEVENTF_KEYUP);
                SendKeyboard(VK_SHIFT, KEYEVENTF_KEYUP);
                gp->prevButton |= XINPUT_GAMEPAD_RIGHT_SHOULDER;
            }
        } break;
        case XINPUT_GAMEPAD_DPAD_UP:
        {
            if ((gp->prevButton & XINPUT_GAMEPAD_DPAD_UP) == 0x0000)
            {
                SendKeyboard(VK_UP, 0);
                SendKeyboard(VK_UP, KEYEVENTF_KEYUP);
                gp->prevButton |= XINPUT_GAMEPAD_DPAD_UP;
            }
        } break;
        case XINPUT_GAMEPAD_DPAD_DOWN:
        {
            if ((gp->prevButton & XINPUT_GAMEPAD_DPAD_DOWN) == 0x0000)
            {
                SendKeyboard(VK_DOWN, 0);
                SendKeyboard(VK_DOWN, KEYEVENTF_KEYUP);
                gp->prevButton |= XINPUT_GAMEPAD_DPAD_DOWN;
            }
        } break;
        case XINPUT_GAMEPAD_DPAD_LEFT:
        {
            if ((gp->prevButton & XINPUT_GAMEPAD_DPAD_LEFT) == 0x0000)
            {
                SendKeyboard(VK_LEFT, 0);
                SendKeyboard(VK_LEFT, KEYEVENTF_KEYUP);
                gp->prevButton |= XINPUT_GAMEPAD_DPAD_LEFT;
            }
        } break;
        case XINPUT_GAMEPAD_DPAD_RIGHT:
        {
            if ((gp->prevButton & XINPUT_GAMEPAD_DPAD_RIGHT) == 0x0000)
            {
                SendKeyboard(VK_RIGHT, 0);
                SendKeyboard(VK_RIGHT, KEYEVENTF_KEYUP);
                gp->prevButton |= XINPUT_GAMEPAD_DPAD_RIGHT;
            }    
        } break;
        default: 
        {
            if ((gp->prevButton & XINPUT_GAMEPAD_A) == XINPUT_GAMEPAD_A) SendMouse(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE, cursorPos);
            gp->prevButton = 0x0000;
        } break;
    }

    POINT cursorMove = { 0, 0 };
    if ((abs(gp->LeftStickX) - gp->deadZoneLeft) > 0)
    {
        cursorMove.x = (abs(gp->LeftStickX) >> 12) & 15;
        cursorMove.x = cursorMove.x << 1;
        if (gp->LeftTrigger == 1) cursorMove.x = cursorMove.x >> 2;
        if (gp->LeftStickX < 0) cursorMove.x *= -1;
    }
    if ((abs(gp->LeftStickY) - gp->deadZoneLeft) > 0)
    {
        cursorMove.y = (abs(gp->LeftStickY) >> 12) & 15;
        cursorMove.y = cursorMove.y << 1;
        if (gp->LeftTrigger == 1) cursorMove.y = cursorMove.y >> 2;
        if (gp->LeftStickY > 0) cursorMove.y *= -1;
    }

    //cursorPos = cursorPos + cursorMove; 
    if (cursorMove != POINT{ 0,0 })
    {
        SendMouse(MOUSEEVENTF_MOVE, cursorMove);
    }

    SHORT mouseWheel = 0;

    if ((abs(gp->RightStickY) - gp->deadZoneRight) > 0)
    {
        mouseWheel = (abs(gp->RightStickY) >> 12) & 15;
        mouseWheel <<= 1;
        if (gp->RightTrigger == 0) mouseWheel <<= scrollSpeed;
        if (gp->RightStickY < 0) mouseWheel *= -1;
    }

    if (mouseWheel != 0)
    {
        SendMouse(MOUSEEVENTF_WHEEL | MOUSEEVENTF_ABSOLUTE, cursorPos, mouseWheel);
    }

    //printf("%p\n",currentWindow);
    //printf("0x%04x\n", gp->Button);
    //printf("Left x:%d y:%d\n", gp->LeftStickX, gp->LeftStickY);
}

int main(int argc, char* argv[])
{
    //hXbox = GetXboxControllerNumber();
    //if (hXbox > 4) return -1;
    scrollSpeed = 3;
    Gamepad g1 = Gamepad();
    while (g1.IsConnected() == 0)
    {
        Sleep(1000);
        g1.ResetHXboxId();
    }
    while (g1.IsConnected() == 1)
    {
        g1.Refresh();
        MouseControl(&g1);
        Sleep(10);
    }
    return 0;
}