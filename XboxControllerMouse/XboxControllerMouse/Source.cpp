#include <cstdlib>
#include <cstdio>
#include <Windows.h>
#include "Gamepad.h"
#include "DefaultControl.h"

int main(int argc, char* argv[])
{

    ShowWindow(GetConsoleWindow(), SW_MINIMIZE);

    Gamepad g1 = Gamepad();
    Control* c1;

    //replace with your class
    DefaultControl dc1 = DefaultControl(&g1);
    
    c1 = &dc1;

    // END replace with your class

    while (g1.IsConnected() == 0)
    {
        Sleep(500);
        g1.ResetHXboxId();
    }
    while (g1.IsConnected() == 1)
    {
        g1.Refresh();
        c1->MouseControl();
        Sleep(10);
    }
    return 0;
}
