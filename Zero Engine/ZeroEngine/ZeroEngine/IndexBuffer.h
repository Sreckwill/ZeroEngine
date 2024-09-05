#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
	//class for Creating the IndexBuffer
	class IndexBuffer
	{
	private:
		//creating the  Render ID for string the IndexBuffer
		unsigned int m_RenderID;
	public:
		//constructor for Assiging the IndexBuffer
		IndexBuffer();
		//destructor for Deleting the IndexBuffer
		~IndexBuffer();
		//Bind the IndexBuffer
		void Bind() const;
		//UnBind the IndexBuffer
		void UnBind() const;
	
		//test addition
	};

