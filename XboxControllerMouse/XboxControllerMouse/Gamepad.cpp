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

void Gamepad::CheckBatteryStatus()
{
    if(this->IsConnected()) XInputGetBatteryInformation(this->hXbox, BATTERY_DEVTYPE_GAMEPAD, &this->batteryStatus);
}

void Gamepad::ShowBatteryStatus()
{
    if (this->IsConnected())
    {
        printf("Battery type: ");
        switch (this->batteryStatus.BatteryType)
        {
            case BATTERY_TYPE_DISCONNECTED: printf("Device disconnected\n"); break;
            case BATTERY_TYPE_WIRED: printf("Wired connection\n"); break;
            case BATTERY_TYPE_ALKALINE: printf("Alkaline battery\n"); break;
            case BATTERY_TYPE_NIMH: printf("NiMH battery\n"); break;
            case BATTERY_TYPE_UNKNOWN: printf("Unknown\n"); break;
        }
        if (this->batteryStatus.BatteryType > BATTERY_TYPE_WIRED && this->batteryStatus.BatteryType < BATTERY_TYPE_UNKNOWN)
        {
            printf("Battery level: ");
            switch (this->batteryStatus.BatteryLevel)
            {
                case BATTERY_LEVEL_EMPTY: printf("EMPTY\n"); break;
                case BATTERY_LEVEL_LOW: printf("LOW\n"); break;
                case BATTERY_LEVEL_MEDIUM: printf("MEDIUM\n"); break;
                case BATTERY_LEVEL_FULL: printf("FULL\n"); break;
            }
        }

    }
    
}
