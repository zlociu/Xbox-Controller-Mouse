#pragma once
#include "Control.h"

class DefaultControl : public Control
{
public:
	DefaultControl(Gamepad* gp) : Control(gp) {}

	void MouseControl();
};

