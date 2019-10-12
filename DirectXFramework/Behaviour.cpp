#include "Behaviour.h"
#include <math.h>
void RotateQ::process()
{
	//std::cout << "\nRotateQ";
	
	if (GetKeyState('Q') & 0x8000)
	{
		rotationRad +=1.0f* XM_PI / 180;
	}
	if (GetKeyState('E') & 0x8000)
	{
		rotationRad -= 1.0f* XM_PI / 180;
	}
	if (rotationRad > XM_PIDIV2)
	{
		gameobject->transform->Translate(XMVectorSet(0,1.0f/FRAME_RATE,0,0));
	}
	if (rotationRad < XM_PIDIV2)
	{
	//
		//gameobject->transform->Translate(XMVectorSet(0, -1.0f / FRAME_RATE, 0, 0));
	}
	//std::cout << "\n" << rotationangle;
	gameobject->transform->RotateLC(axis,rotationRad);
}

RotateQ::RotateQ(float val, XMVECTOR axis)
{
	
	rotationRad = val* XM_PI/180;
	this->axis = axis;
}

RotateAround::RotateAround(const RotateAround & ob)
{
	axis = ob.axis;
	angle = ob.angle;
	point = ob.point;
}

void RotateAround::process()
{
	//std::cout << "\nRA";
	gameobject->transform->RotateAround(point, axis, angle);
}

RotateV::RotateV(float x1, float y1, float z1)
{
	x = x1* XM_PI/180;
	y = y1* XM_PI/180;
	z = z1* XM_PI/180;
}

RotateV::RotateV(XMVECTOR vector)
{
	x = vector.m128_f32[0];
	y = vector.m128_f32[1];
	z = vector.m128_f32[2];
}

void RotateV::process()
{
	gameobject->transform->Rotate(x,y,z);
}

void Controller::process()
{
	if (GetKeyState('W') & 0x8000)
	{
		gameobject->transform->Translate(gameobject->transform->Forward() * speed / (FLOAT)FRAME_RATE);
	}
	if (GetKeyState('A') & 0x8000)
	{
		gameobject->transform->Translate(gameobject->transform->Left() * speed / (FLOAT)FRAME_RATE);
	}
	if (GetKeyState('S') & 0x8000)
	{
		gameobject->transform->Translate(gameobject->transform->Back() * speed / (FLOAT)FRAME_RATE);
	}
	if (GetKeyState('D') & 0x8000)
	{
		gameobject->transform->Translate(gameobject->transform->Right() * speed / (FLOAT)FRAME_RATE);
	}
	if (GetKeyState('R') & 0x8000)
	{
		gameobject->transform->Translate(gameobject->transform->Up() * speed / (FLOAT)FRAME_RATE);
	}
	if (GetKeyState('F') & 0x8000)
	{
		gameobject->transform->Translate(gameobject->transform->Down() * speed / (FLOAT)FRAME_RATE);
	}
	//gameobject->transform->Rotate(XMVectorSet(0.0f,1.0f,0.0f,0.0f) ,angle * Framework::instanse().mouse.RawInput.x);
	//gameobject->transform->Rotate(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), angle * Framework::instanse().mouse.RawInput.y);
	//не трогать. smileyface
	gameobject->transform->RotateWR(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), angle * Framework::instanse().mouse.RawInput.x);
	gameobject->transform->RotateWR(gameobject->transform->Right()/*XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)*/, angle * Framework::instanse().mouse.RawInput.y);//bug
	/*if (GetKeyState('G') & 0x8000)
	{
		gameobject->transform->Rotate(gameobject->transform->Right(), angle);
	}
	if (GetKeyState('T') & 0x8000)
	{
		gameobject->transform->Rotate(gameobject->transform->Right(), -angle);
	}
	if (GetKeyState('V') & 0x8000)
	{
		gameobject->transform->Rotate(gameobject->transform->Up(), angle);
	}
	if (GetKeyState('B') & 0x8000)
	{
		gameobject->transform->Rotate(gameobject->transform->Up(), -angle);
	}*/
}
