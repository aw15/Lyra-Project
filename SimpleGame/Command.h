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
	Vector2D dir;
public:
	MoveCommand();
	virtual void Execute(Object* object);


};



class FireCommand : public Command
{
public:
	virtual void Execute(Object* object);
};