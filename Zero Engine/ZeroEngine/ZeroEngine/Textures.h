#pragma once
#include "GL/glew.h"
#include <string>
using std::string;
class Textures {
private:
public:
	Textures();
	virtual ~Textures();

	bool LoadTexture(const string& fileName, bool generateMipMaps = true);
	void Bind(GLuint texUnit = 0);
	void UnBind(GLuint texUnit = 0);

private:
	Textures(const Textures& rhs) {}
	Textures& operator = (const Textures& rhs) {}

	unsigned int  mTexture;
 
};

