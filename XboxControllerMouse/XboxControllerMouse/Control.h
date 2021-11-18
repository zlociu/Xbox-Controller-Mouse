#pragma once
#include "Gamepad.h"
#include "Windows.h"
#include "XInput.h"
#include "LogicHelper.h"

class Control
{
protected: 
	Gamepad* gamepad;

	POINT cursorPos;
	SHORT scrollSpeed;

public: 
	Control(Gamepad* gp) : gamepad(gp) { scrollSpeed = 3; GetCursorPos(&cursorPos); }

	Control(Gamepad* gp, short sclSpeed) : gamepad(gp), scrollSpeed(sclSpeed) { GetCursorPos(&cursorPos); }

	//basic functions to send single mouse or keyboard command (mouse click up/down or key up/down)
protected:
	/// <summary>
	/// Send single mouse command using <c>SendInput</c> function.
	/// </summary>
	/// <param name="dwFlags">- command to execute (button click / scroll)</param>
	/// <param name="curPos">- cursor position </param>
	/// <param name="mouseData">- uses only with scroll command</param>
	void SendMouse(DWORD dwFlags, POINT curPos, DWORD mouseData = 0);

	/// <summary>
	/// Send single keyboard command using <see cref="SendInput"/> function.
	/// <see href="https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes"> vKey </see> 
	/// </summary>
	/// <param name="vKey">- virtual key number. For all values see: </param>
	/// <param name="dwFlags">- command to execute (key up/down)</param>
	void SendKeyboard(WORD vKey, DWORD dwFlags);

protected:

	/// <summary>
	/// Click left mouse button. 
	/// </summary>
	/// <param name="xButton">- XINPUT button</param>
	void SendLeftMouseClick(WORD xButton);

	/// <summary>
	/// Click and hold left mouse button.
	/// </summary>
	/// <param name="xButton">- XINPUT button</param>
	void SendLeftMouseHold(WORD xButton);

	/// <summary>
	/// Release clicked left mouse button. <para/>
	/// When 'SendLeftMouseHold' is used, this has to be called in 'default' statement in 'switch' in 'MouseControl' function.
	/// </summary>
	/// <param name="xButton">- XINPUT button</param>
	void SendLeftMouseRelease(WORD xButton);

	/// <summary>
	/// Click right mouse button.
	/// </summary>
	/// <param name="xButton">- XINPUT button</param>
	void SendRightMouseClick(WORD xButton);

	/// <summary>
	/// Click middle mouse button (scroll button).
	/// </summary>
	/// <param name="xButton">- XINPUT button</param>
	void SendMiddleMouseClick(WORD xButton);

	/// <summary>
	/// Combine two keyboard keys (e.g. CTRL+C). <para/>
	/// First button will be released last.
	/// </summary>
	/// <param name="xButton">- XINPUT button</param>
	/// <param name="vKey1">- first key</param>
	/// <param name="vKey2">- second key</param>
	void SendMacroKeyboard(WORD xButton, WORD vKey1, WORD vKey2);

	/// <summary>
	/// Combine three keyboard keys (e.g. ALT+CTRL+DELETE). <para/>
	/// First button will be released last.
	/// </summary>
	/// <param name="xButton">- XINPUT button</param>
	/// <param name="vKey1">- first key</param>
	/// <param name="vKey2">- second key</param>
	/// <param name="vKey3">- third key</param>
	void SendMacroKeyboard(WORD xButton, WORD vKey1, WORD vKey2, WORD vKey3);

	/// <summary>
	/// Click single keyboard key.
	/// </summary>
	/// <param name="xButton">- XINPUT button</param>
	/// <param name="vKey">- key</param>
	void SendOneKey(WORD xButton, WORD vKey);

	/// <summary>
	/// Press one key and hold.
	/// </summary>
	/// <param name="xButton">- XINPUT button</param>
	/// <param name="vKey">- key</param>
	void SendOneKeyHold(WORD xButton, WORD vKey);

	/// <summary>
	/// Release pressed key. 
	/// When 'SendOneKeyHold' is used, this has to be called in 'default' statement in 'switch' in 'MouseControl' function.
	/// </summary>
	/// <param name="xButton">- XINPUT button</param>
	/// <param name="vKey">- key</param>
	void SendOneKeyRelease(WORD xButton, WORD vKey);

	/// <summary>
	/// Change scroll speed. <para/>
	/// 3 ^ value
	/// </summary>
	/// <param name="value">- xor value</param>
	void ChangeScrollSpeed(int value);

	/// <summary>
	/// Move cursor using left thumb and change speed using left trigger.
	/// </summary>
	void CursorControlLeft();

	/// <summary>
	/// Move cursor using right thumb and change speed using right trigger.
	/// </summary>
	void CursorControlRigth();

	/// <summary>
	/// Scroll using left thumb and change speed using left trigger.
	/// </summary>
	void ScrollControlLeft();

	/// <summary>
	/// Scroll using right thumb and change speed using right trigger.
	/// </summary>
	void ScrollControlRight();

public: 
	virtual void MouseControl() = 0;
};

