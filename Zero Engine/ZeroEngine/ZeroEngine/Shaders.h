#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
class Shaders
{
private:
	unsigned int shaderProgram;
public:
	std::string readShaderFile(const std::string& filename);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int CreateShaderProgram(std::string& vertexShader, std::string& fragmentShader);
	void SetUniformLoaction4f(unsigned int shaderProgram, float r, float g, float b, float a);
};

