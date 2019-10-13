#pragma once
#include "Component.h"
#include "SystemDefs.h"
#include "Framework.h"
#include <iostream>

class Framework;
class Gameobject;
class DXManager;

class Camera: virtual public Component
{
	public:	
		Layout ComponentType(){return Layout::GameLogic;};
	XMMATRIX g_view;
	XMMATRIX g_Projection;
	Camera();
	~Camera();
	void *operator new(size_t size)
	{
		//std::cout << "\ncamera is aligned by " << 16;
		void* p = _aligned_malloc(size, 16);
		if(!p)
		throw std::bad_alloc();

		return p;
	}

	void process();
	
};


