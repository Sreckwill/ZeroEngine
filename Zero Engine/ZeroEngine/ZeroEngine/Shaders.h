#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>

//Class for the Shaders
class Shaders
{
private:
	//Storeing the ShaderProgram
	unsigned int shaderProgram;
public:

	void UseProgram(unsigned int shaderProgram);
	//funtion for the reading the .shader file for the Device
	std::string readShaderFile(const std::string& filename);
	//function for creating and compile the Shader
	unsigned int compileShader(unsigned int type, const std::string& source);
	//funtion for the creating the ShaderProgram
	unsigned int CreateShaderProgram(std::string& vertexShader, std::string& fragmentShader);
	//funtion for setting the Uniform varaiable 
	void SetUniformLoaction(unsigned int shaderProgram, float r, float g, float b, float a, const  char* name);
	void SetUnifromLoaction(unsigned int shaderProgram,const  char* name);
	void SetUnifromLoaction(unsigned int shaderProgram, float size,const  char* name);
	void SetunifromLoaction(unsigned int shaderPrgram, const  glm::vec2& v, const  char* name);
	void SetunifromLoaction(unsigned int shaderPrgram, const  glm::vec3& v, const  char* name);
	void SetunifromLoaction(unsigned int shaderPrgram, const  glm::vec4& v, const  char* name);
	void SetunifromLoaction(unsigned int shaderPrgram, const  glm::mat4& v, const  char* name);
};

