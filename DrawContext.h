#ifndef DRAWCONTEXT_H_
#define DRAWCONTEXT_H_

#include "GL/glew.h"

class CDrawContext
{

private:

	int m_ShaderProgramID;
	GLuint m_2DVertexBuffer, m_2DElementBuffer;

	void Create2DVertexBuffer();

public:

	void Calculate2DProjectionMatrix( int, int );
	void Draw2DVertexBuffer();
	void Bind2DVertexBuffer();
	void Unbind2DVertexBuffer();

	void UseShaderProgram( int id )
	{

	    m_ShaderProgramID = id;
	    glUseProgram( id );

	}

	void SetShaderProgram( int id )
	{

		m_ShaderProgramID = id;

	}

	void Initialize();

	~CDrawContext();

};

#endif
