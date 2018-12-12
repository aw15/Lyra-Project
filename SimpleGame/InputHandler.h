#pragma once
#include"Command.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void handleInput();

private:
	Command* buttonLeft = new MoveCommand();
	Command* buttonRight = new MoveCommand();
	Command* buttonUp = new MoveCommand();
	Command* buttonDown = new MoveCommand();
};




