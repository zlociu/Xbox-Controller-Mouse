#include "DefaultControl.h"

void DefaultControl::MouseControl()
{
    GetCursorPos(&cursorPos);

    // buttons
    switch (gamepad->Button)
    {
        case XINPUT_GAMEPAD_A:
        {
            // START own function
            DefaultControl::SendLeftMouseHold(XINPUT_GAMEPAD_A);
            // END own function
        } break;
        case XINPUT_GAMEPAD_B:
        {
            // START own function
            DefaultControl::SendRightMouseClick(XINPUT_GAMEPAD_B);
            // END own function
        } break;
        case XINPUT_GAMEPAD_X: 
        {
            // START own function
            DefaultControl::SendOneKey(XINPUT_GAMEPAD_X, VK_BACK);
            // END own function
        } break;
        case XINPUT_GAMEPAD_Y:
        {
            // START own function
            DefaultControl::SendOneKey(XINPUT_GAMEPAD_Y, VK_ESCAPE);
            // END own function
        } break;
        case XINPUT_GAMEPAD_START:
        {
            // START own function
            DefaultControl::SendOneKey(XINPUT_GAMEPAD_START, VK_LWIN);
            // END own function
        } break;
        case XINPUT_GAMEPAD_BACK: 
        {
            // START own function

            // END own function
        }break;
        case XINPUT_GAMEPAD_LEFT_THUMB:
        {
            // START own function
            DefaultControl::SendMacroKeyboard(XINPUT_GAMEPAD_LEFT_THUMB, VK_CONTROL, 0x43);
            // END own function
        } break;
        case XINPUT_GAMEPAD_RIGHT_THUMB:
        {
            // START own function
            DefaultControl::ChangeScrollSpeed(5);
            // END own function
        } break;
        case XINPUT_GAMEPAD_LEFT_SHOULDER:
        {
            // START own function
            DefaultControl::SendOneKey(XINPUT_GAMEPAD_LEFT_SHOULDER, VK_BROWSER_BACK);
            // END own function
        } break;
        case XINPUT_GAMEPAD_RIGHT_SHOULDER:
        {
            // START own function
            DefaultControl::SendOneKey(XINPUT_GAMEPAD_RIGHT_SHOULDER, VK_BROWSER_FORWARD);
            // END own function
        } break;
        case XINPUT_GAMEPAD_DPAD_UP:
        {
            // START own function
            DefaultControl::SendOneKey(XINPUT_GAMEPAD_DPAD_UP, VK_UP);
            // END own function
        } break;
        case XINPUT_GAMEPAD_DPAD_DOWN:
        {
            // START own function
            DefaultControl::SendOneKey(XINPUT_GAMEPAD_DPAD_DOWN, VK_DOWN);
            // END own function
        } break;
        case XINPUT_GAMEPAD_DPAD_LEFT:
        {
            // START own function
            DefaultControl::SendOneKey(XINPUT_GAMEPAD_DPAD_LEFT, VK_LEFT);
            // END own function
        } break;
        case XINPUT_GAMEPAD_DPAD_RIGHT:
        {
            // START own function
            DefaultControl::SendOneKey(XINPUT_GAMEPAD_DPAD_RIGHT, VK_RIGHT);
            // END own function
        } break;
        default:
        {
            // START release functions (only when __Hold() functions were called)
            DefaultControl::SendLeftMouseRelease(XINPUT_GAMEPAD_A);

            // END release functions
            

            // do NOT delete this
            gamepad->prevButton = 0x0000;
            // END do NOT delete this
        } break;
    }

    // START sterring cursor & scroll

    DefaultControl::CursorControlLeft();
    DefaultControl::ScrollControlRight();

    // DefaultControl::CursorControlRight();
    // DefaultControl::ScrollControlLeft();

    // END sterring cursor& scroll
}
