#pragma once
#include"Command.h"


class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	Command* HandleInput(char key, KeyStatus status);
	Command* HandleAI(const AIState state);

private:
	Command* jump = new JumpCommand(); //경량패턴 적용.
	Command* idle = new IdleCommand();
	Command* moveLeft = new MoveCommand(-1.f, 0.f, 0.f);
	Command* moveRight = new MoveCommand(1.f, 0.f, 0.f);

public:
	Command* key_f = new AirAttackCommand();
	Command* key_a = moveLeft;
	Command* key_d = moveRight;
	Command* key_space = jump;

//KEY UP///////////////////////////////////////////////////
	Command* keyUp_a = idle;
	Command* keyUp_d = idle;
	Command* keyUp_f = idle;
};




