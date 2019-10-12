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

	XMMATRIX g_view;
	XMMATRIX g_Projection;
	//XMFLOAT4X4 g_view;
	//XMFLOAT4X4 g_Projection;
	XMMATRIX GetView();
	void SetView(CXMMATRIX view);
	XMMATRIX GetProjection();
	void SetProjection(CXMMATRIX proj);
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


