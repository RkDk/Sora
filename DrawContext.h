#ifndef DRAWCONTEXT_H_
#define DRAWCONTEXT_H_

#include "GL/glew.h"

#include "Matrix.h"

class CDrawContext
{

private:

	int m_ShaderProgramID;
	GLuint m_2DVertexBuffer, m_2DElementBuffer;

	CMatrix< float > * m_pViewMatrix, * m_pModelMatrix;

	void Create2DVertexBuffer();

public:

	void Calculate2DProjectionMatrix( int, int );
	void UpdateCameraMatrix();
	void Draw2DVertexBuffer();
	void Bind2DVertexBuffer();
	void Unbind2DVertexBuffer();

	void SetViewMatrix( CMatrix< float > * pViewMatrix )
	{

		m_pViewMatrix = pViewMatrix;

	}

	void SetModelMatrix( CMatrix< float > * pModelMatrix )
	{

		m_pModelMatrix = pModelMatrix;

	}

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
