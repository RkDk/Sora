#ifndef DRAWCONTEXT_H_
#define DRAWCONTEXT_H_

#include "GL/glew.h"

#include "Matrix.h"

class CDrawContext
{

private:

	int m_ShaderProgramID;
	GLuint m_2DVertexBuffer, m_2DElementBuffer;
	GLint m_ModelMatUniform, m_ViewMatUniform;

	CMatrix< float > * m_pViewMatrix, * m_pModelMatrix;

	void Create2DVertexBuffer();

public:

	void Calculate2DProjectionMatrix( int, int );
	void Draw2DVertexBuffer();
	void Bind2DVertexBuffer();
	void Unbind2DVertexBuffer();

	void UpdateViewMatrix();
    void UpdateModelMatrix();

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

	    if( m_ShaderProgramID != id )
        {

            glUseProgram( id );

            m_ShaderProgramID = id;
            m_ViewMatUniform = -1;
            m_ModelMatUniform = -1;

        }

	}

	void Initialize();

	~CDrawContext();

};

#endif
