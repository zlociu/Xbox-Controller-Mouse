# Xbox-Controller-Mouse 🎮 

## About
Control Your computer with Xbox One gamepad.  
Turn on application and plug in your Xbox controller, wired or wireless via Bluetooth.  
Working only on Windows.  

## Decscription 📋
### Features 
- mouse buttons & scroll functions
- keyboard keys (single)
- keyboard macros (up to 3 keys)
- creating own profiles

### Create own profile 💻
If You want to create new profile, changing some of gamepad rules please read this part.
1. Create new class which inherit from `Control` class. In file ___OwnControl.h___ it should be:
```cpp
#pragma once
#include "Control.h"

class OwnControl : public Control
{
public:
	OwnControl(Gamepad* gp) : Control(gp) {}

	void MouseControl();
};
```
2. In ___OwnControl.cpp___ write `MouseControl()` implementation.
    1. Easiest way to implement `MouseControl()` function is to copy from ___DefaultControl.cpp___.
    2. Replace given functions between _START_ and _END_ comment blocks.
    ```cpp
    case XINPUT_GAMEPAD_A:
        {
            // START own function
            DefaultControl::SendLeftMouseHold(XINPUT_GAMEPAD_A);
            // END own function
        } break;
    ...
    ```
    3. In ___Control.h___ are defined available functions you can use. You can also create new functions.
3. In ___Source.cpp___ in `Main()` function replace with your own class.
```cpp
Gamepad g1 = Gamepad();
Control* c1;

//replace with your class
DefaultControl dc1 = DefaultControl(&g1);
c1 = &dc1;
// END replace with your class
...
```
4. Build and run new version of application.

## Compile & Run 🛠️ 
Easiest way to compile is use Visual Studio.  
Just open project and click build and then run.  
Program will automatically detect your device.  
Program will automatically close when you disconnect gamepad.  

## Future improvements 💡
 - Battery check and alert if low energy.
