#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <stdio.h>

class Gamepad
{
private:
    DWORD hXbox;
    XINPUT_STATE xboxState;
    BOOL connected;
    XINPUT_BATTERY_INFORMATION batteryStatus;
public:
    const int deadZoneLeft;
    const int deadZoneRight;
    // control button state, prevent spaming key or mouse
    WORD prevButton;

public:
    Gamepad() : deadZoneLeft(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE), deadZoneRight(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
    {
        DWORD dwResult;
        connected = 0;
        hXbox = 5;

        for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
        {
            XINPUT_STATE state;
            ZeroMemory(&state, sizeof(XINPUT_STATE));
            // Simply get the state of the controller from XInput.
            dwResult = XInputGetState(i, &state);

            if (dwResult == ERROR_SUCCESS)
            {
                hXbox = i;
                connected = 1;
                break;
            }
        }
    }
    Gamepad(int dzL, int dzR) : deadZoneLeft(dzL), deadZoneRight(dzR)
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
            }
        }
        connected = false;
    }

    // public variables
    WORD Button;
    BOOL LeftTrigger;
    BOOL RightTrigger;
    SHORT LeftStickX;
    SHORT LeftStickY;
    SHORT RightStickX;
    SHORT RightStickY;

    // public functions
    void Refresh();
    BOOL IsConnected();
    void ResetHXboxId();
    void ShowBatteryStatus();
    void CheckBatteryStatus();
};
