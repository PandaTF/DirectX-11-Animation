#pragma once
#include <DirectXMath.h>
#include <vector>
using namespace DirectX;

#define NUM_JOINTS 28

struct SimpleVertex
{
	SimpleVertex() {}
	SimpleVertex(float x, float y, float z,
		float r, float g, float b, float a,
		float u, float v,
		float nx, float ny, float nz,
		float vr, float vg, float vb, float va,
		float tx, float ty, float tz,
		float bx, float by, float bz,
		int joint1, int joint2, int joint3, int joint4,
		float weight1, float weight2, float weight3, float weight4)
		: Pos(x, y, z), Color(r, g, b, a), Normal(nx, ny, nz), texCoord(u, v),
		vertexColor(vr, vg, vb, va), tangent(tx, ty, tz), binormal(bx, by, bz),
		jointIndices(joint1, joint2, joint3, joint4), 
		weights(weight1, weight2, weight3, weight4) {};

	XMFLOAT3 Pos;
	XMFLOAT4 Color;
	XMFLOAT2 texCoord;
	XMFLOAT3 Normal;

	XMFLOAT4 vertexColor;
	XMFLOAT3 tangent;
	XMFLOAT3 binormal;

	XMINT4 jointIndices;
	XMFLOAT4 weights;
};

struct myMatrix
{
	double x1, x2, x3, x4;
	double y1, y2, y3, y4;
	double z1, z2, z3, z4;
	double w1, w2, w3, w4;
};

struct Keyframe
{
	double time;
	std::vector<myMatrix> translateMatrx;
};

struct Joint
{
	int mParentIndex;
	myMatrix myMatrix;
};

struct clip
{
	bool hasAnimation;
	double duration = 0.0f;
	std::vector<Keyframe> frame;
};

struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;

	// x - Normal/Bump Mapping
	// y - Specular Mapping
	// z - isDebugRender
	XMFLOAT4 mapControl;

	//Diffuse Light
	XMFLOAT4 ambient;
	XMFLOAT4 vLightDir[2];
	XMFLOAT4 vLightColor[2];
	XMFLOAT4 vOutputColor;
	
	//Point Light
	XMFLOAT4 vPointLightColor;
	XMFLOAT4 vPointLightPos;
	XMFLOAT3 vPointLightAttenuation;
	float PointLightRange;
	
	XMFLOAT4 cameraPosition;
	XMFLOAT4 specularColor;
	float specularPower;
	XMFLOAT3 padding1;
};

struct ConstantBuffer_DR
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;

	XMMATRIX translateMatrix[NUM_JOINTS];
	float hasAnimation;
	XMFLOAT3 padding;
};

struct ConstantBuffer_SkinnedAnimation
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;

	// x - Normal/Bump Mapping
	// y - Specular Mapping
	// z - isDebugRender
	XMFLOAT4 mapControl;

	//Diffuse Light
	XMFLOAT4 ambient;
	XMFLOAT4 vLightDir[2];
	XMFLOAT4 vLightColor[2];
	XMFLOAT4 vOutputColor;

	//Point Light
	XMFLOAT4 vPointLightColor;
	XMFLOAT4 vPointLightPos;
	XMFLOAT3 vPointLightAttenuation;
	float PointLightRange;

	XMFLOAT4 cameraPosition;
	XMFLOAT4 specularColor;
	float specularPower;
	XMFLOAT3 padding1;

	XMMATRIX translateMatrix[NUM_JOINTS];
};