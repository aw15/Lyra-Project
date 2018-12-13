#include "stdafx.h"
#include "Command.h"


Command::Command()
{
}


Command::~Command()
{
}

void MoveCommand::Execute(Object * object)
{
	object->Move(dir);
}

void FireCommand::Execute(Object * object)
{
	object->Fire();
}

void JumpCommand::Execute(Object * object)
{
}
