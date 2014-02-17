#include "DrawContext.h"

CDrawContext::~CDrawContext()
{

	glDeleteBuffers( 1, &m_VertexBuffer );
	glDeleteBuffers( 1, &m_ElementBuffer );

}

void CDrawContext::CalculateProjectionMatrix( int width, int height )
{

	GLfloat fWidth = width;
	GLfloat fHeight = height;

	const GLfloat projMat[] =
	{

		2.0f / fWidth, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / -fHeight, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f

	};

	GLint matUniform = glGetUniformLocation( m_ShaderProgramID, "ProjView" );
	glUniformMatrix4fv( matUniform, 1, GL_FALSE, projMat );

}

void CDrawContext::DrawVertexBuffer()
{

	glDrawElements( GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, ( void * )0 );

}

void CDrawContext::BindVertexBuffer()
{

	glBindBuffer( GL_ARRAY_BUFFER, m_VertexBuffer );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, ( void * )0 );

}

void CDrawContext::UnbindVertexBuffer()
{

	glDisableVertexAttribArray( 0 );

}

void CDrawContext::CreateVertexBuffer()
{

	GLfloat vertex_buffer_data[] = {
               
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
               
	};
       
	GLushort element_buffer_data[] = {
               
		3, 0, 1, 3, 2, 1
               
	};
       
	glGenBuffers( 1, &m_VertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, m_VertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertex_buffer_data ), vertex_buffer_data, GL_STATIC_DRAW );
       
	glGenBuffers( 1, &m_ElementBuffer );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( element_buffer_data ), element_buffer_data, GL_STATIC_DRAW );

}

void CDrawContext::Initialize()
{

	CreateVertexBuffer();

}