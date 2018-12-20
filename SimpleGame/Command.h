#pragma once
class Object;
class Command
{
public:
	Command();
	virtual void Execute(Object& object) = 0;
	virtual ~Command();
};

class IdleCommand : public Command
{
public:
	virtual void Execute(Object& object);
};

class MoveCommand : public Command
{
	Vector3D dir;
public:
	MoveCommand(float x, float y, float z) { dir.x = x; dir.y = y; dir.z = z; }
	virtual void Execute(Object& object);
};

class JumpCommand : public Command
{
public:
	virtual void Execute(Object& object);
};

class AirAttackCommand : public Command
{
public:
	virtual void Execute(Object& object);
};