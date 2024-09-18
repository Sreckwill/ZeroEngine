#ifndef VertexArray

#include "GL/glew.h"
class VertexArray
{
private:
	unsigned int m_RenderID;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;

	void GenArray();
	void DeleteArray();

};

#endif // !VertexArray



