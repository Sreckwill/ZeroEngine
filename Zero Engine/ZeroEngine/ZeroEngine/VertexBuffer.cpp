#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() :m_RenderID(0)
{
}

VertexBuffer::~VertexBuffer()
{
	DeleteBuffer();
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::GenBuffer()
{
	glGenBuffers(1, &m_RenderID);
}

void VertexBuffer::DeleteBuffer()
{
	glDeleteBuffers(1, &m_RenderID);
}
