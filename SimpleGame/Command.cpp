#include "stdafx.h"
#include "Command.h"


Command::Command()
{
}


Command::~Command()
{
}

void MoveCommand::Execute(Object& object)
{
	object.Move(dir);
}


void JumpCommand::Execute(Object& object)
{
}

void IdleCommand::Execute(Object & object)
{
	object.Idle();
}

void AirAttackCommand::Execute(Object & object)
{
	object.AirAttack();
}
