#include "stdafx.h"
#include "InputHandler.h"


InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}

Command* InputHandler::handleInput(char key)
{
	
	if (key == 'a') return key_a;
	if (key == 'd') return key_d;
	if (key == 'w') return key_w;
	if (key == 's') return key_s;

	return nullptr;
}
