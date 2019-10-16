#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <new.h>

#include "Camera.h"
#include "Framework.h"
#include "MeshRenderer.h"
#include "Behaviour.h"



SimpleVertex Pyramidvertices[] =
{	/* координаты X, Y, Z				цвет R, G, B, A				*/
	{ XMFLOAT3(0.0f,  1.5f,  0.0f), XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-1.2f,  0.0f, -1.2f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(1.2f,  0.0f, -1.2f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(-1.2f,  0.0f,  1.2f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
	{ XMFLOAT3(1.2f,  0.0f,  1.2f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) }
};

WORD Pyramidindices[] =
{	// индексы массива vertices[], по которым строятся треугольники
	0,2,1,	/* Треугольник 1 = vertices[0], vertices[2], vertices[3] */
	0,3,4,	/* Треугольник 2 = vertices[0], vertices[3], vertices[4] */
	0,1,3,	/* и т. д. */
	0,4,2,
	1,2,3,
	2,4,3,
};

SimpleVertex Cubevertices[] =
{	/* координаты X, Y, Z				цвет R, G, B, A					 */
	{ XMFLOAT3(1.0f,  2.0f,  -1.0f), XMFLOAT4(0.0f, 0.0f, 4.0f, 1.0f) },
	{ XMFLOAT3(-1.0f,  2.0f,  1.0f), XMFLOAT4(0.0f, 0.0f, 4.0f, 1.0f) },
	{ XMFLOAT3(1.0f,  2.0f,  1.0f), XMFLOAT4(0.0f, 0.0f, 4.0f, 1.0f) },
	{ XMFLOAT3(-1.0f,  2.0f,  -1.0f), XMFLOAT4(0.0f, 0.0f, 4.0f, 1.0f) },
	{ XMFLOAT3(-1.0f,  0.0f, -1.0f), XMFLOAT4(4.0f, 4.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(1.0f,  0.0f, -1.0f), XMFLOAT4(4.0f, 4.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-1.0f,  0.0f,  1.0f), XMFLOAT4(4.0f, 4.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(1.0f,  0.0f,  1.0f), XMFLOAT4(4.0f, 4.0f, 0.0f, 1.0f) }
};

WORD Cubeindices[] =
{	// индексы массива vertices[], по которым строятся треугольники
	0,1,2,	
	1,0,3,
	3,5,4,	
	5,3,0,
	2,5,0,
	5,2,7,
    2,6,7,
	6,2,1,
    1,3,6,
	3,4,6,
	4,5,6,
	6,5,7,
};




int main(int argc, char *argv[])
{
	try
	{
	Framework::instanse().Initialize("XD");
	MeshRenderer *PyrMR = new MeshRenderer(Pyramidvertices, Pyramidindices, 18,5);
	MeshRenderer *CubeMR = new MeshRenderer(Cubevertices,Cubeindices,36,8);
	
	PyrMR->InitShader("urok4.fx");
	
	if (FAILED(PyrMR->InitMesh()))
	{
		std::cout << "\nfailed init mesh";
		throw 1;
	}
	if (FAILED(CubeMR->InitMesh()))
	{
		std::cout << "\nfailed init mesh";
		throw 1;
	}

	if (FAILED(Framework::instanse().dxmanager->InitMatrixes(Framework::instanse().g_hWnd)))
	{
		std::cout << "failed init matrixes";
		throw 1;
	}

	Gameobject* P1 = new Gameobject();
	Gameobject* Player = new Gameobject();
	Gameobject* C1 = new Gameobject();
	Gameobject* C2 = new Gameobject();
	Gameobject* C3 = new Gameobject();
	C1->transform->Position = XMVectorSet(-2.0f,0.0f,0.0f,0.0f);
	C1->transform->LocalScale = XMVectorSet(0.5f,0.5f,0.5f,0.0f);
	C2->transform->Position = XMVectorSet(0.0f, 2.1f, 0.0f, 0.0f);
	C2->transform->LocalScale = XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f);
	C3->transform->Position = XMVectorSet(-2.2f, 0.0f, 0.0f, 0.0f);
	C3->transform->LocalScale = XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f);

	//void *ptr;
	//ptr = _aligned_malloc(sizeof(Camera),16);
	
	//Camera * cam = ptr; //new Camera();

	//Camera* cam = new(_aligned_malloc(sizeof(Camera), 16)) Camera();
	Camera* cam = new Camera();
	
	std::cout <<"\n cam address " << cam;
	//getch();
	//std::cout <<"\n cam bytes" << sizeof(Camera);

	Framework::instanse().camera = cam;
	Controller* cont = new Controller(2.0f, 5.0f);
	RotateQ *rotateQ = new RotateQ(30.0f/FRAME_RATE, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	RotateQ *RotQ = new RotateQ(30.0f/FRAME_RATE,XMVectorSet(1.0f,1.0f,1.0f,0.0f));

	Translator *trans = new Translator(XMVectorSet(-1.0f / FRAME_RATE, 0, 0.0f, 0));
	Translator *trans2 = new Translator(XMVectorSet(1.0f / FRAME_RATE, 0, 0.0f, 0));
	RotateAround *rotatearoundY = new RotateAround(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 30.0f / FRAME_RATE);
	RotateAround *rotatearoundX = new RotateAround(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), 30.0f / FRAME_RATE);
	RotateAround *rotatearoundZ = new RotateAround(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), 30.0f / FRAME_RATE);

	//RotateAround *rotatearound2 = new RotateAround(*rotatearound);

	//Pyramid->AddComponent(rotateQ);
	//
	//gameobject->AddComponent(trans);
	
	Player->AddComponent(cam);
	Player->AddComponent(cont);
	Player->transform->Position = XMVectorSet(0.0f,1.0f,0.0f,0.0f);

	//C1->AddComponent(rotatearound);
	C1->AddComponent(rotatearoundY);
	C1->AddComponent(CubeMR);
	//C1->AddComponent(RotQ);
	C2->AddComponent(new MeshRenderer(*CubeMR));
	C2->AddComponent(rotatearoundX);

	C3->AddComponent(new MeshRenderer(*CubeMR));
	C3->AddComponent(rotatearoundZ);
	//Pyramid->AddComponent(rotatearound2);
	//P1->AddComponent(rotateQ);
	//P1->AddComponent(rotateQ);
	P1->AddComponent(PyrMR);
	P1->transform->LocalScale = XMVectorSet(1.0f,0.25f,1.0f,0.0f);

	Framework::instanse().AddGameobject(Player); 
	Framework::instanse().AddGameobject(P1);
	Framework::instanse().AddGameobject(C1);
	Framework::instanse().AddGameobject(C2);
	Framework::instanse().AddGameobject(C3);
	//delelop
	Framework::instanse().Run();
	}
	catch (std::exception e)
	{
		MessageBox(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
	}
	catch (...)
	{
		MessageBox(nullptr, "wat", "Error", MB_OK | MB_ICONERROR);
	}
	return 0;
}