#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

	class IndexBuffer
	{
	private:
		unsigned int m_RenderID;
	public:
		IndexBuffer();
		~IndexBuffer();
		void Bind() const;
		void UnBind() const;
	

};

