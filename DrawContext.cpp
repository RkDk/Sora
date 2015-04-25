#include "DrawContext.h"

CDrawContext::~CDrawContext()
{

	glDeleteBuffers( 1, &m_2DVertexBuffer );
	glDeleteBuffers( 1, &m_2DElementBuffer );
    glDeleteBuffers( 1, &m_2DColorBuffer );
    glDeleteBuffers( 1, &m_2DSTBuffer );
    
    glDeleteVertexArrays( 1, & m_2DVertexArray );

}

void CDrawContext::StartDraw() {
 
    m_CurDrawingMatrix.Identity();
    
    glBindVertexArray( m_2DVertexArray );
    
}

void CDrawContext::EndDraw() {
    
    UpdateModelMatrix( &m_CurDrawingMatrix );
    
    Bind2DVertexBuffer();
    Draw2DVertexBuffer();
    
}

void CDrawContext::SetTexture( GLuint texture ) {
    
    glBindTexture( GL_TEXTURE_2D, texture );
    
}


void CDrawContext::SetGlobalScale( float x, float y ) {
 
    m_DrawScale.Set( x, y );
    
}

void CDrawContext::DrawGLTexture( GLuint texture, float x, float y, float width, float height, float r, float g, float b, float a ) {
    
    if( texture > 0 )
        glBindTexture( GL_TEXTURE_2D, texture );

    CMatrix< float > mat;
    
    mat.Identity();
    mat.Translate( x, y, 0.0f );
    mat.Scale( width * m_DrawScale.GetX(), height * m_DrawScale.GetY(), 1.0f );
    
    glBindVertexArray( m_2DVertexArray );
    
    UpdateModelMatrix( &mat );
    SetDrawColor( r, g, b, a );
    SetTexCoord( 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f );
    
    Bind2DVertexBuffer();
    Draw2DVertexBuffer();
    
}

void CDrawContext::DrawMaterial( CTextureImage & material, int frame, float x, float y, float width, float height, float r, float g, float b, float a ) {
    
    DrawGLTexture( material.GetFrame( frame ).GetTexture(), x, y, width, height, r, g, b, a );
}

void CDrawContext::DrawMaterial( CTextureImage & material, float x, float y, float width, float height, float r, float g, float b, float a ) {
    
    DrawGLTexture( material.GetFrame( 0 ).GetTexture(), x, y, width, height, r, g, b, a );
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

void CDrawContext::Bind2DVertexArray() {
 
    glBindVertexArray( m_2DVertexArray );
    
}

void CDrawContext::Bind2DVertexBuffer()
{
    
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );
    
    Bind2DVertexArray();

	glBindBuffer( GL_ARRAY_BUFFER, m_2DVertexBuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_2DElementBuffer );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, ( void * )0 );
	
    glBindBuffer( GL_ARRAY_BUFFER, m_2DColorBuffer );
    glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 0, ( void * )0 );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_2DSTBuffer );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, ( void * )0 );
    
}

void CDrawContext::Unbind2DVertexBuffer()
{

	glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
    
}

void CDrawContext::SetScale( float width, float height ) {
    
    m_CurDrawingMatrix.Scale( width, height, 1.0f );
    
}

void CDrawContext::SetPos( float x, float y ) {
    
    m_CurDrawingMatrix.SetTranslate( x, y, 0.0f );
    
}

void CDrawContext::SetTexCoord( float t1x, float t1y, float t2x, float t2y, float t3x, float t3y, float t4x, float t4y ) {
 
    GLfloat st_buffer_data[] = {
        
        t1x, t1y,
        t2x, t2y,
        t3x, t3y,
        t4x, t4y
        
    };
    
    glBindBuffer( GL_ARRAY_BUFFER, m_2DSTBuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof( st_buffer_data ), st_buffer_data, GL_DYNAMIC_DRAW );
    
}

void CDrawContext::SetDrawColor( float r, float g, float b, float a )
{
    
    GLfloat color_buffer_data[] = {
      
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
    
    glGenBuffers( 1, &m_2DSTBuffer );
    SetTexCoord( 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f );
    
}

void CDrawContext::Initialize()
{

	Create2DVertexBuffer();
	m_ShaderProgramID = -1;
    
    m_DrawScale.Set( 1.0f, 1.0f );

}
