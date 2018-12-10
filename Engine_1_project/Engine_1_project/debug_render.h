#pragma once

#ifndef _DEBUG_RENDER_H_
#define _DEBUG_RENDER_H_

#define MAX_LINE_VERTS 4096

#include <D3D11.h>
#include <DirectXMath.h>
#include <vector>
using namespace DirectX;

class DEBUG_RENDER
{
private:
	struct VertexType
	{
		VertexType() {}
		VertexType(float x, float y, float z,
			float r, float g, float b, float a,
			float jointIndex, float pad1, float pad2, float pad3)
			: Pos(x, y, z), Color(r, g, b, a), JointIndex(jointIndex, pad1, pad2, pad3) {};

		XMFLOAT3 Pos;
		XMFLOAT4 Color;
		XMFLOAT4 JointIndex;
	};

	struct LineType
	{
		float x, y, z;
		float r, g, b, a;

		float jointIndex;
	};

public:
	DEBUG_RENDER();
	DEBUG_RENDER(const DEBUG_RENDER&);
	~DEBUG_RENDER();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	void add_line(ID3D11Device*, XMVECTOR point_a, XMVECTOR point_b, XMVECTOR color_a, XMVECTOR color_b);
	void add_line_animation(ID3D11Device*, XMVECTOR point_a, XMVECTOR point_b, XMVECTOR color_a, XMVECTOR color_b, float jointChild, float jointParent);
	void clear_lines();
	const LineType* get_line_verts(unsigned index);
	unsigned int GetNumOfLines();
	unsigned int GetNumOfPoints();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	unsigned int line_vert_count;
	std::vector<LineType*> line_verts;
};

#endif