#pragma once


//--------------------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// ����������� ������
//--------------------------------------------------------------------------------------
Texture2D txDiffuse : register(t0);		// ����� ��������
SamplerState samLinear : register(s0);	// ����� �������

cbuffer ConstantBuffer : register(b0)
{
	matrix World;			// ������� ����
	matrix View;			// ������� ����
	matrix Projection;		// ������� ��������
}


//--------------------------------------------------------------------------------------
struct VS_INPUT					// �������� ������ ���������� �������
{
	float4 Pos : POSITION;		// ������� �� X, Y, Z
	float2 Tex : TEXCOORD0;		// ���������� �������� �� tu, tv
};

struct PS_INPUT					// �������� ������ ����������� �������
{
	float4 Pos : SV_POSITION;	// ������� ������� � �������� (��������)
	float2 Tex : TEXCOORD0;		// ���������� �������� �� tu, tv
	
};


//--------------------------------------------------------------------------------------
// ��������� ������
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	output.Pos = mul(input.Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	output.Tex = input.Tex;

	return output;
}


//--------------------------------------------------------------------------------------
// ���������� ������ ��� ����
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	float4 finalColor = (0,0,0,1);
	/*
	// ���������� ������������ ������� �� ���� ���������� �����
	for (int i = 0; i < 2; i++)
	{
		finalColor += saturate(dot((float3)vLightDir[i], input.Norm) * vLightColor[i]);
	}
	finalColor.a = 1;
	*/
	finalColor *= txDiffuse.Sample(samLinear, input.Tex);

	return finalColor;
}


//--------------------------------------------------------------------------------------
// ���������� ������ ��� ���������� �����
//--------------------------------------------------------------------------------------
float4 PSSolid(PS_INPUT input) : SV_Target
{
	return (float4)1;
}
