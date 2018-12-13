#pragma once
class Object;
class Command
{
public:
	Command();
	virtual void Execute(Object* object) = 0;
	virtual ~Command();
};


class MoveCommand : public Command
{
	Vector3D dir;
public:
	MoveCommand(float x, float y, float z) { dir.x = x; dir.y = y; dir.z = z; }
	virtual void Execute(Object* object);
};

class JumpCommand : public Command
{
public:
	virtual void Execute(Object* object);
};

class FireCommand : public Command
{
public:
	virtual void Execute(Object* object);
};