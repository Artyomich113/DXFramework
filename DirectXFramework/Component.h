#pragma once
#include "Mouse/MouseClass.h"

class Gameobject;

class Component
{

public:
	enum Layout
	{
		Render,
		GameLogic,
	};
	Gameobject *gameobject;
	virtual void process() = 0;
	virtual Layout ComponentType() = 0;
};



