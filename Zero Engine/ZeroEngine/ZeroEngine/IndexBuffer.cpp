#include "IndexBuffer.h"
//constructor for Assiging the VertexBuffer
IndexBuffer::IndexBuffer()
{
	//Generating the Buffer
	glGenBuffers(1, &m_RenderID);
	//Binding the Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
}

IndexBuffer::~IndexBuffer()
{
	//Deleting the Buffer
	glDeleteBuffers(1, &m_RenderID);
}

void IndexBuffer::Bind() const
{
	//Binding the Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
}

void IndexBuffer::UnBind() const
{
	//Un Bind the Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
