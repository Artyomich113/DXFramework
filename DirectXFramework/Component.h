#pragma once
#include "Mouse/MouseClass.h"

class Gameobject;

class Component
{
public:
	Gameobject *gameobject;
	virtual void process() = 0;
};



