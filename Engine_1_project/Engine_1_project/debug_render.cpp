#include "debug_render.h"

DEBUG_RENDER::DEBUG_RENDER()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;

	m_vertexCount = 0;
	m_indexCount = 0;
	line_vert_count = 0;

	line_verts.reserve(0);
}

DEBUG_RENDER::DEBUG_RENDER(const DEBUG_RENDER &)
{
}

DEBUG_RENDER::~DEBUG_RENDER()
{
}

bool DEBUG_RENDER::Initialize(ID3D11Device *device)
{
	bool result;
	
	if (line_verts.size() != 0)
		clear_lines();
	
	if (line_vert_count == 0)
		return true;
	
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	return true;
}

void DEBUG_RENDER::Shutdown()
{
	//clear_lines();
	
	for (unsigned int i = 0; i < line_verts.size(); i++)
	{
		if (line_verts[i])
		{
			delete line_verts[i];
			line_verts[i] = 0;
		}
	}

	ShutdownBuffers();
}

void DEBUG_RENDER::Render(ID3D11DeviceContext *deviceContext)
{
	RenderBuffers(deviceContext);

	return;
}

int DEBUG_RENDER::GetIndexCount()
{
	return m_indexCount;
}

void DEBUG_RENDER::add_line(ID3D11Device* device, XMVECTOR point_a, XMVECTOR point_b, XMVECTOR color_a, XMVECTOR color_b)
{
	if (line_vert_count * 2 < MAX_LINE_VERTS - 2)
	{
		LineType *temp1, *temp2;
		temp1 = new LineType();
		temp2 = new LineType();

		temp1->x = XMVectorGetX(point_a);
		temp1->y = XMVectorGetY(point_a);
		temp1->z = XMVectorGetZ(point_a);

		temp1->r = XMVectorGetX(color_a);
		temp1->g = XMVectorGetY(color_a);
		temp1->b = XMVectorGetZ(color_a);
		temp1->a = XMVectorGetW(color_a);

		line_verts.push_back(temp1);

		temp2->x = XMVectorGetX(point_b);
		temp2->y = XMVectorGetY(point_b);
		temp2->z = XMVectorGetZ(point_b);

		temp2->r = XMVectorGetX(color_b);
		temp2->g = XMVectorGetY(color_b);
		temp2->b = XMVectorGetZ(color_b);
		temp2->a = XMVectorGetW(color_b);

		line_verts.push_back(temp2);

		line_vert_count++;
		m_vertexCount = line_vert_count * 2;
		m_indexCount = m_vertexCount;

		InitializeBuffers(device);
	}
	else
		return;
}

void DEBUG_RENDER::add_line_animation(ID3D11Device *device, XMVECTOR point_a, XMVECTOR point_b, XMVECTOR color_a, XMVECTOR color_b, float jointChild, float jointParent)
{
	if (line_vert_count * 2 < MAX_LINE_VERTS - 2)
	{
		LineType *temp1, *temp2;
		temp1 = new LineType();
		temp2 = new LineType();

		temp1->x = XMVectorGetX(point_a);
		temp1->y = XMVectorGetY(point_a);
		temp1->z = XMVectorGetZ(point_a);

		temp1->r = XMVectorGetX(color_a);
		temp1->g = XMVectorGetY(color_a);
		temp1->b = XMVectorGetZ(color_a);
		temp1->a = XMVectorGetW(color_a);

		temp1->jointIndex = jointChild;

		line_verts.push_back(temp1);

		temp2->x = XMVectorGetX(point_b);
		temp2->y = XMVectorGetY(point_b);
		temp2->z = XMVectorGetZ(point_b);

		temp2->r = XMVectorGetX(color_b);
		temp2->g = XMVectorGetY(color_b);
		temp2->b = XMVectorGetZ(color_b);
		temp2->a = XMVectorGetW(color_b);

		temp2->jointIndex = jointParent;

		line_verts.push_back(temp2);

		line_vert_count++;
		m_vertexCount = line_vert_count * 2;
		m_indexCount = m_vertexCount;

		InitializeBuffers(device);
	}
	else
		return;
}

void DEBUG_RENDER::clear_lines()
{
	for (unsigned int i = 0; i < line_verts.size(); i++)
	{
		line_verts[i]->x = line_verts[i]->y = line_verts[i]->z = 0.0f;
		line_verts[i]->r = line_verts[i]->g = line_verts[i]->b = line_verts[i]->a = 0.0f;
	}

	line_vert_count = 0;
	m_vertexCount = 0;
	m_indexCount = 0;
}

const DEBUG_RENDER::LineType * DEBUG_RENDER::get_line_verts(unsigned index)
{
	if (line_verts[index])
	{
		return line_verts[index];
	}
	else
		return nullptr;
}

unsigned int DEBUG_RENDER::GetNumOfLines()
{
	return line_vert_count;
}

unsigned int DEBUG_RENDER::GetNumOfPoints()
{
	return (unsigned int)line_verts.size();
}

bool DEBUG_RENDER::InitializeBuffers(ID3D11Device *device)
{
	VertexType* vertices = nullptr;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	for (int i = 0; i < m_vertexCount; i++)
	{
		vertices[i] = VertexType(line_verts[i]->x, line_verts[i]->y, line_verts[i]->z,
			line_verts[i]->r, line_verts[i]->g, line_verts[i]->b, line_verts[i]->a, line_verts[i]->jointIndex, 0.0f, 0.0f, 0.0f);

		indices[i] = i;
	}

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType)*m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)*m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void DEBUG_RENDER::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}

void DEBUG_RENDER::RenderBuffers(ID3D11DeviceContext *deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	return;
}
