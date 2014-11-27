#include "DrawContext.h"

CDrawContext::~CDrawContext()
{

	glDeleteBuffers( 1, &m_2DVertexBuffer );
	glDeleteBuffers( 1, &m_2DElementBuffer );
    glDeleteBuffers( 1, &m_2DColorBuffer );
    
    glDeleteVertexArrays( 1, & m_2DVertexArray );

}

void CDrawContext::Calculate2DProjectionMatrix( int width, int height )
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

void CDrawContext::UpdateModelMatrix( CMatrix< float > * modelMat )
{

    if( m_ModelMatUniform < 0 )
        m_ModelMatUniform = glGetUniformLocation( m_ShaderProgramID, "ModelMat" );

	glUniformMatrix4fv( m_ModelMatUniform, 1, GL_FALSE, modelMat->GetRawMatrix() );

}

void CDrawContext::UpdateViewMatrix( CMatrix< float > * viewMat )
{
    if( m_ViewMatUniform < 0 )
        m_ViewMatUniform = glGetUniformLocation( m_ShaderProgramID, "ViewMat" );

	glUniformMatrix4fv( m_ViewMatUniform, 1, GL_FALSE, viewMat->GetRawMatrix() );

}

void CDrawContext::Draw2DVertexBuffer()
{

	glDrawElements( GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, ( void * )0 );

}

void CDrawContext::Bind2DVertexBuffer()
{
    
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );

	glBindBuffer( GL_ARRAY_BUFFER, m_2DVertexBuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_2DElementBuffer );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, ( void * )0 );
	
    glBindBuffer( GL_ARRAY_BUFFER, m_2DColorBuffer );
    glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 0, ( void * )0 );
    
}

void CDrawContext::Unbind2DVertexBuffer()
{

	glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    
}

void CDrawContext::SetDrawColor( float r, float g, float b, float a )
{
    
    GLfloat color_buffer_data[] = {
      
        r, g, b, a,
        r, g, b, a,
        r, g, b, a,
        r, g, b, a,
        r, g, b, a,
        r, g, b, a
        
    };
    
    glBindBuffer( GL_ARRAY_BUFFER, m_2DColorBuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof( color_buffer_data ), color_buffer_data, GL_DYNAMIC_DRAW );
    
}

void CDrawContext::Create2DVertexBuffer()
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
    
    glGenVertexArrays( 1, &m_2DVertexArray );
    glBindVertexArray( m_2DVertexArray );
    
	glGenBuffers( 1, &m_2DVertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, m_2DVertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertex_buffer_data ), vertex_buffer_data, GL_STATIC_DRAW );

	glGenBuffers( 1, &m_2DElementBuffer );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_2DElementBuffer );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( element_buffer_data ), element_buffer_data, GL_STATIC_DRAW );
    
    glGenBuffers( 1, &m_2DColorBuffer );
    SetDrawColor( 1.0f, 1.0f, 1.0f, 1.0f );
    
}

void CDrawContext::Initialize()
{

	Create2DVertexBuffer();
	m_ShaderProgramID = -1;

}
