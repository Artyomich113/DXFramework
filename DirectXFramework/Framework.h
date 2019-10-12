#pragma once

#include"DXManager.h"
#include "Camera.h"
#include "Transform.h"
#include "Gameobject.h"
#include "resource.h"
#include "SystemDefs.h"
#include "Mouse/MouseClass.h"
#include <string>
#include <cstring>
#include <list>

//class DXManager;
class Gameobject;
class Camera;

class Framework
{
	Framework();
	~Framework();
public:
	
	static Framework& instanse()
	{
		static Framework framework;
		return framework;
	}
	MouseClass mouse;
	bool Initialize(std::string name);
	Camera* camera;
	DXManager* GetDXManager(){return dxmanager;}
	std::list<Gameobject*> gameobjects;
	void AddGameobject(Gameobject*);
	MSG Run();
	void proceedAllGameobjects();
	//private:
	bool CreateDXWindow(std::string name, int x, int y, int height, int wight);
	std::string name;
	DXManager *dxmanager;
	HINSTANCE g_hIns;
	HWND g_hWnd;
};


