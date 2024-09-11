#include "VertexArray.h"

VertexArray::VertexArray() :m_RenderID(0)
{

}

VertexArray::~VertexArray()
{
	DeleteArray();
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RenderID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::GenArray()
{
	glGenVertexArrays(1, &m_RenderID);
}

void VertexArray::DeleteArray()
{
	glDeleteVertexArrays(1, &m_RenderID);
}
