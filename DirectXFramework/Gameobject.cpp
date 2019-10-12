#include "Gameobject.h"
#include "Transform.h"
#include <iostream>

void Gameobject::procedure()
{
//std::cout << "\ngameobject procedure";
	for (auto iter = components.begin(); iter != components.end(); iter++)
	{
		(*iter)->process();
	}
}

void Gameobject::AddComponent(Component * component)
{
	components.push_back(component);
	component->gameobject = this;
}

Gameobject::Gameobject()
{
	transform = new Transform();
}

Gameobject::~Gameobject()
{
	/*for (auto it = components.begin(); it != components.end(); it++)
	{
		delete (*it);
	}*/
	delete transform;
}