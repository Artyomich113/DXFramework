#include <iostream>

#include "Camera.h"
#include "Framework.h"
#include "Mesh/MeshRenderer.h"
#include "Mesh/MeshRendererUI.h"
#include "Mesh/MeshRendererTextured.h"
#include "Mesh/Mesh.h"
#include "Behaviour.h"

SimpleVertex Pyramidvertices[] =
{	/* ���������� X, Y, Z				���� R, G, B, A				*/
	{ XMFLOAT3(0.0f,  1.5f,  0.0f), XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-1.0f,  0.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
	{ XMFLOAT3( 1.0f,  0.0f, -1.0f), XMFLOAT4(0.0f, 0.9f, 0.9f, 1.0f) },
	{ XMFLOAT3(-1.0f,  0.0f,  1.0f), XMFLOAT4(0.0f, 0.8f, 0.8f, 1.0f) },
	{ XMFLOAT3( 1.0f,  0.0f,  1.0f), XMFLOAT4(0.0f, 0.7f, 0.7f, 1.0f) }
};

WORD Pyramidindices[] =
{	// ������� ������� vertices[], �� ������� �������� ������������
	0,2,1,	/* ����������� 1 = vertices[0], vertices[2], vertices[3] */
	0,3,4,	/* ����������� 2 = vertices[0], vertices[3], vertices[4] */
	0,1,3,	/* � �. �. */
	0,4,2,
	1,2,3,
	2,4,3,
};

TexturedVertex CubeverticesTextured[] =
{
	{ XMFLOAT3(1.0f,  2.0f,  -1.0f), XMFLOAT2(1.0f, 1.0f) },
	{ XMFLOAT3(-1.0f,  2.0f,  1.0f), XMFLOAT2(0.0f, 0.0f) },
	{ XMFLOAT3(1.0f,  2.0f,  1.0f),  XMFLOAT2(1.0f, 0.0f) },
	{ XMFLOAT3(-1.0f,  2.0f,  -1.0f),XMFLOAT2(0.0f, 1.0f) },
	{ XMFLOAT3(-1.0f,  0.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
	{ XMFLOAT3(1.0f,  0.0f, -1.0f),  XMFLOAT2(1.0f, 0.0f) },
	{ XMFLOAT3(-1.0f,  0.0f,  1.0f), XMFLOAT2(1.0f, 1.0f) },
	{ XMFLOAT3(1.0f,  0.0f,  1.0f),  XMFLOAT2(0.0f, 0.0f) }
};

TexturedVertex PlaneVertex[] =
{
	{ XMFLOAT3(-0.5f,  0.0f,  -0.5f), XMFLOAT2(0.0f, 0.0f) },
	{ XMFLOAT3(-0.5f,  0.0f,  0.5f), XMFLOAT2(0.0f, 50.0f) },
    { XMFLOAT3(0.5f,  0.0f,  0.5f), XMFLOAT2(50.0f, 50.0f) },
    { XMFLOAT3(0.5f,  0.0f,  -0.5f), XMFLOAT2(50.0f, 0.0f) },
};

WORD PlaneIndices[] = 
{
	0,1,3,
	3,1,2,
};

SimpleVertex Cubevertices[] =
{	/* ���������� X, Y, Z				���� R, G, B, A					 */
	{ XMFLOAT3(1.0f,  2.0f,  -1.0f), XMFLOAT4(0.0f, 0.0f, 2.0f, 1.0f) },
	{ XMFLOAT3(-1.0f,  2.0f,  1.0f), XMFLOAT4(0.0f, 0.0f, 3.0f, 1.0f) },
	{ XMFLOAT3(1.0f,  2.0f,  1.0f), XMFLOAT4(0.0f, 0.0f, 4.0f, 1.0f) },
	{ XMFLOAT3(-1.0f,  2.0f,  -1.0f), XMFLOAT4(0.0f, 0.0f, 5.0f, 1.0f) },
	{ XMFLOAT3(-1.0f,  0.0f, -1.0f), XMFLOAT4(2.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(1.0f,  0.0f, -1.0f), XMFLOAT4(3.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(-1.0f,  0.0f,  1.0f), XMFLOAT4(4.0f, 0.0f, 0.0f, 1.0f) },
	{ XMFLOAT3(1.0f,  0.0f,  1.0f), XMFLOAT4(5.0f, 0.0f, 0.0f, 1.0f) }
};

WORD Cubeindices[] =
{	// ������� ������� vertices[], �� ������� �������� ������������
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
		auto *PyrMR = new MeshRendererUI(Pyramidvertices, Pyramidindices, 18, 5);
		if (FAILED(PyrMR->InitShader("UIShader.fx")))
		{
			std::cout << "\nfailed init shader urok4";
			throw 1;
		}

		auto *CubeMR = new MeshRenderer(Cubevertices, Cubeindices, 36, 8);
		if (FAILED(CubeMR->InitShader("urok4.fx")))
		{
			std::cout << "\nfailed init shader urok4";
			throw 1;
		}

		auto *CubeTex = new MeshRendererTextured("josuka.dds", CubeverticesTextured, Cubeindices, 36, 8);

		
		if (FAILED(CubeTex->InitShader("TextureShader.fx")))
		{
			std::cout << "\nfailed init shader urok4";
			throw 1;
		}
		


		auto *PlaneTex = new MeshRendererTextured("josuka.dds", PlaneVertex, PlaneIndices, 6, 4);
		
		if (FAILED(PlaneTex->InitShader("TextureShader.fx")))
		{
			std::cout << "\nfailed init shader urok4";
			throw 1;
		}
		


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
		if (FAILED(CubeTex->InitMesh()))
		{
			std::cout << "\nfailed init meshTex";
			throw 1;
		}
		if (FAILED(PlaneTex->InitMesh()))
		{
			std::cout << "\nfailed init meshTex";
			throw 1;
		}

		/*
		if (FAILED(Framework::instanse().dxmanager->InitMatrixes(Framework::instanse().g_hWnd)))
		{
			std::cout << "failed init matrixes";
			throw 1;
		}
		*/

		Gameobject* P1 = new Gameobject("P1");
		Gameobject* Plane = new Gameobject("Plane");
		Gameobject* Player = new Gameobject("Player");
		Gameobject* C1 = new Gameobject("C1");
		Gameobject* C2 = new Gameobject("C2");
		Gameobject* C3 = new Gameobject("C3");
		P1->transform->Position = XMVectorSet(-0.0f, -0.0f, 0.0f, 0.0f);
		P1->transform->LocalScale = XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f) / 3;

		Plane->transform->Position = XMVectorSet(0.0f, -5.0f, 0.0f, 0.0f);
		Plane->transform->LocalScale = XMVectorSet(50.0f, 1.f, 50.0f, 0.0f);


		C1->transform->Position = XMVectorSet(-2.0f, 0.0f, 0.0f, 0.0f);
		C1->transform->LocalScale = XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f);

		C2->transform->Position = XMVectorSet(0.0f, 2.1f, 0.0f, 0.0f);
		C2->transform->LocalScale = XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f);

		C3->transform->Position = XMVectorSet(-2.2f, 0.0f, 0.0f, 0.0f);
		C3->transform->LocalScale = XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f);


		Camera* cam = new Camera();


		Framework::instanse().camera = cam;
		Controller* cont = new Controller(2.0f, 5.0f);
		//RotateQ *rotateQ = new RotateQ(30.0f/FRAME_RATE, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
		RotateQ *RotQ111 = new RotateQ(30.0f / FRAME_RATE, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

		//Translator *trans = new Translator(XMVectorSet(-1.0f / FRAME_RATE, 0, 0.0f, 0));
		//Translator *trans2 = new Translator(XMVectorSet(1.0f / FRAME_RATE, 0, 0.0f, 0));
		RotateAround *rotatearoundY = new RotateAround(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 30.0f / FRAME_RATE);
		RotateAround *rotatearoundX = new RotateAround(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), 30.0f / FRAME_RATE);
		RotateAround *rotatearoundZ = new RotateAround(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), 30.0f / FRAME_RATE);

		//RotateAround *rotatearound2 = new RotateAround(*rotatearound);

		//Pyramid->AddComponent(rotateQ);
		
		//gameobject->AddComponent(trans);

		Player->AddComponent(cam);
		Player->AddComponent(cont);
		Player->transform->Position = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		//C1->AddComponent(rotatearound);
		C1->AddComponent(rotatearoundY);
		C1->AddComponent(CubeMR);
		//C1->AddComponent(RotQ);
		C2->AddComponent(new MeshRenderer(*CubeMR));
		C2->AddComponent(rotatearoundX);

		C3->AddComponent(CubeTex);
		C3->AddComponent(rotatearoundZ);
		
		//Pyramid->AddComponent(rotatearound2);
		//P1->AddComponent(rotateQ);
		//P1->AddComponent(rotateQ);
		//P1->AddComponent(RotQ111);
		//P1->AddComponent(PyrMR);

		Plane->AddComponent(PlaneTex);



		Framework::instanse().AddGameobject(Player);
		//Framework::instanse().AddGameobject(P1);
		Framework::instanse().AddGameobject(C1);
		Framework::instanse().AddGameobject(C2);
		Framework::instanse().AddGameobject(C3);
		Framework::instanse().AddGameobject(Plane);
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
	//Framework::instanse().~Framework();
	//system("pause");
	return 0;
}