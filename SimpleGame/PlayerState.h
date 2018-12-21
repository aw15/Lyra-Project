#pragma once


class ObjectState
{
public:
	virtual ~ObjectState() {};
	virtual string handleInput(Object& object,char key, KeyStatus status) = 0;
};


class MoveState : public ObjectState
{
public:
	virtual ~MoveState() {};
	virtual string handleInput(Object& object,char key, KeyStatus status);

private:

};

class IdleState : public ObjectState
{
public:
	virtual ~IdleState() {};
	virtual string handleInput(Object& object,char key, KeyStatus status);
public:

};


