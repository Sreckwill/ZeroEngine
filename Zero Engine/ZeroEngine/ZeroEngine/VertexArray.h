#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
class VertexArray
{
private:
	unsigned int m_RenderID;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;
};

