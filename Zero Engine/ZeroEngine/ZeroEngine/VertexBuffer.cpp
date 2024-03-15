#include "VertexBuffer.h"
//constructor for Assiging the VertexBuffer
VertexBuffer::VertexBuffer()
{
	//Generating the Buffer
	glGenBuffers(1, &m_RenderID);
	//Binding the Buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
}
//destructor for Deleting the Data
VertexBuffer::~VertexBuffer()
{
	//Deleting the Buffer
	glDeleteBuffers(1, &m_RenderID);
}
//Bind the Data
void VertexBuffer::Bind() const
{
	//Bind the Buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
}
//UnBind the Data
void VertexBuffer::UnBind() const
{
	//Un Bind the Buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
