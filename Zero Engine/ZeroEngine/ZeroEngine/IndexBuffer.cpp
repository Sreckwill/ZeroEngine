#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &m_RenderID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RenderID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
