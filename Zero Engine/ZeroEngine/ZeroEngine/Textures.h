
#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "GL/glew.h"
#include <string>
using std::string;

class Texture
{
public:
	Texture();
	virtual ~Texture();

	bool loadTexture(const string& fileName, bool generateMipMaps = true);
	void bind(unsigned int texUnit = 0);
	void unbind(unsigned int texUnit = 0);

private:
	Texture(const Texture& rhs) {}
	Texture& operator = (const Texture& rhs) {}

	unsigned int mTexture;
};
#endif 
