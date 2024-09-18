
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>
#include "GL/glew.h"
#include "glm/glm.hpp"
using std::string;


class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		PROGRAM
	};

	// Only supports vertex and fragment (this series will only have those two)
	bool loadShaders(const char* vsFilename, const char* fsFilename);
	void use();

	unsigned int getProgram() const;

	void setUniform(const char* name, const glm::vec2& v);
	void setUniform(const char* name, const glm::vec3& v);
	void setUniform(const char* name, const glm::vec4& v);
	void setUniform(const char* name, const glm::mat4& m);
	void setUniform(const char* name, const float f);
	void setUniform(const char* name, const GLint v);
	void setUniformSampler(const char* name, const unsigned int & slot);

	// We are going to speed up looking for uniforms by keeping their locations in a map
	GLint getUniformLocation(const char* name);

private:

	string fileToString(const string& filename);
	void  checkCompileErrors(unsigned int shader, ShaderType type);


	unsigned int mHandle;
	std::map<string, GLint> mUniformLocations;
};
#endif // SHADER_H