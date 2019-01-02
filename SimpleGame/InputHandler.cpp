#include "stdafx.h"
#include "InputHandler.h"


InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}

Command* InputHandler::HandleInput(char key,KeyStatus status)
{
	switch (status)
	{
	case KeyStatus::PRESS:
		if (key == 'a') return key_a;
		if (key == 'd') return key_d;
		if (key == 'f')return key_f;
		break;
	case KeyStatus::RELEASE:
		if (key == 'a') return keyUp_a;
		if (key == 'd') return keyUp_d;
		if (key == 'f')return keyUp_f;
		break;
	}
	return nullptr;
}

Command * InputHandler::HandleAI(const AIState state)
{
	switch (state)
	{
	case AIState::IDLE:
		return idle;
	case AIState::MOVE_LEFT:
		return moveLeft;
	case AIState::MOVE_RIGHT:
		return moveRight;
	}



	return nullptr;
}

