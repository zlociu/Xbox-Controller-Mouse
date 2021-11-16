#include "Gamepad.h"

BOOL Gamepad::IsConnected()
{
    return connected;
}

void Gamepad::Refresh()
{
    DWORD result;
    result = XInputGetState(hXbox, &xboxState);
    if (result == ERROR_SUCCESS)
    {
        XINPUT_GAMEPAD* gamepad = &xboxState.Gamepad;
        Button = gamepad->wButtons;
        LeftStickX = gamepad->sThumbLX;
        LeftStickY = gamepad->sThumbLY;
        RightStickX = gamepad->sThumbRX;
        RightStickY = gamepad->sThumbRY;
        LeftTrigger = (gamepad->bLeftTrigger > 0xc0);
        RightTrigger = (gamepad->bRightTrigger > 0xc0);
    }
    else
    {
        connected = false;
    }
}

void Gamepad::ResetHXboxId()
{
    DWORD dwResult;
    for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        // Simply get the state of the controller from XInput.
        dwResult = XInputGetState(i, &state);

        if (dwResult == ERROR_SUCCESS)
        {
            hXbox = i;
            connected = true;
            return;
        }
    }
    connected = false;
}