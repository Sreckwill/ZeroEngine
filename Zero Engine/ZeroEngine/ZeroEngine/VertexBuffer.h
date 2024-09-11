#pragma once
#include "GL/glew.h"
class VertexBuffer
{
private:
	unsigned int m_RenderID;
public:
	VertexBuffer();
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

	void GenBuffer();
	void DeleteBuffer();
};

