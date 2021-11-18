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

	//basic functions to send single mouse or keyboard command (mouse click up/down or key up/down)
protected:
	void SendMouse(DWORD dwFlags, POINT curPos, DWORD mouseData = 0);
	void SendKeyboard(WORD vKey, DWORD dwFlags);

protected:
	void SendLeftMouseClick(WORD xButton);
	void SendLeftMouseHold(WORD xButton);
	void SendLeftMouseRelease(WORD xButton);

	void SendRightMouseClick(WORD xButton);
	void SendMiddleMouseClick(WORD xButton);

	void SendMacroKeyboard(WORD xButton, WORD vKey1, WORD vKey2);
	void SendMacroKeyboard(WORD xButton, WORD vKey1, WORD vKey2, WORD vKey3);

	void SendOneKey(WORD xButton, WORD vKey);
	void SendOneKeyHold(WORD xButton, WORD vKey);
	void SendOneKeyRelease(WORD xButton, WORD vKey);

	void ChangeScrollSpeed(int value);

	void CursorControlLeft();
	void CursorControlRigth();

	void ScrollControlLeft();
	void ScrollControlRight();

public: 
	virtual void MouseControl() = 0;
};

