#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_RenderID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RenderID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
