#include <cstdlib>
#include <cstdio>
#include <Windows.h>
#include "Gamepad.h"
#include "DefaultControl.h"

int main(int argc, char* argv[])
{

    ShowWindow(GetConsoleWindow(), SW_MINIMIZE);

    Gamepad g1 = Gamepad();

    //replace with your class
    DefaultControl dc1 = DefaultControl(&g1);
    // END replace with your class

    Control* c1 = &dc1;

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

//command line options:
/*
* Usage: xboxmouse.exe [--option1 <value1> [--option2 <value2>] ...]
 -lc   --load-config <classname> load config using class (default name: 'default.config')       
 -h    --help                   show this help
 -v    --version                show version number

*/
