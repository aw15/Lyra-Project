#pragma once
#include"Command.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	Command* handleInput(char key);

private:
	Command* jump = new JumpCommand(); //경량패턴 적용.

public:
	Command* key_a = new MoveCommand(-1,0,0);
	Command* key_d = new MoveCommand(1,0,0);
	Command* key_w = new MoveCommand(0,1,0);
	Command* key_s = new MoveCommand(0,-1,0);
	Command* key_space = jump;
};




