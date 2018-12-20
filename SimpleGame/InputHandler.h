#pragma once
#include"Command.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	Command* handleInput(char key, KEY_STATUS status);

private:
	Command* jump = new JumpCommand(); //경량패턴 적용.
	Command* idle = new IdleCommand();
public:
	Command* key_f = new AirAttackCommand();
	Command* key_a = new MoveCommand(-1.f,0.f,0.f);
	Command* key_d = new MoveCommand(1.f,0.f,0.f);
	Command* key_w = new MoveCommand(0.f,1.f,0.f);
	Command* key_s = new MoveCommand(0.f,-1.f,0.f);
	Command* key_space = jump;

//KEY UP///////////////////////////////////////////////////
	Command* keyUp_a = idle;
	Command* keyUp_d = idle;
	Command* keyUp_w = idle;
	Command* keyUp_s = idle;
};




