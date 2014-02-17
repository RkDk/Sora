#ifndef DRAWCONTEXT_H_
#define DRAWCONTEXT_H_

#include "GL/glew.h"

class CDrawContext
{

private:
	
	int m_ShaderProgramID;
	GLuint m_VertexBuffer, m_ElementBuffer;

	void CreateVertexBuffer();

public:

	void CalculateProjectionMatrix( int, int );
	void DrawVertexBuffer();
	void BindVertexBuffer();
	void UnbindVertexBuffer();

	void SetShaderProgramID( int id )
	{

		m_ShaderProgramID = id;

	}

	void Initialize();

	~CDrawContext();

};

#endif
