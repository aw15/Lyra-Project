#include "stdafx.h"
#include "InputHandler.h"


InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}

Command* InputHandler::handleInput(char key,KEY_STATUS status)
{
	switch (status)
	{
	case KEY_STATUS::PRESS:
		if (key == 'a') return key_a;
		if (key == 'd') return key_d;
		if (key == 'w') return key_w;
		if (key == 's') return key_s;
		if (key == 'f')return key_f;
		break;
	case KEY_STATUS::RELEASE:
		if (key == 'a') return keyUp_a;
		if (key == 'd') return keyUp_d;
		if (key == 'w') return keyUp_w;
		if (key == 's') return keyUp_s;
	}
	return nullptr;
}

