#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
//class for Creating the VertexBuffer
class VertexBuffer
{
private:
	//creating the  Render ID for string the VertexBuffer
	unsigned int m_RenderID;
public:
	//constructor for Assiging the VertexBuffer
	VertexBuffer();
	//destructor for Deleting the VertexBuffer
	~VertexBuffer();
	//Bind the VertexBuffer
	void Bind() const;
	//UnBind the VertexBuffer
	void UnBind() const;
};

