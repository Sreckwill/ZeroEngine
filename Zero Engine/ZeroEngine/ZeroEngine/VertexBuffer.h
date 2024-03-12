#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
class VertexBuffer
{
private:
	unsigned int m_RenderID;
public:
	VertexBuffer();
	~VertexBuffer();
	void Bind() const;
	void UnBind() const;
};

