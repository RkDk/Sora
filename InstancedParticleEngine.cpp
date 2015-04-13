#include "InstancedParticleEngine.h"

void CInstancedParticleEngine::Init( int n, int offset ) {

    m_MaxParticles = n;
    m_ViewMat = new float[ n * 16];
    m_Color = new float[n * 4];
    
    m_Size.resize( n );
    
    InitShader( offset );
    
    
}

void CInstancedParticleEngine::InitShader( int offset ) {
 
    m_ShaderOffset = offset;
    
    BindVertexBuffers( true, false );

    
}

void CInstancedParticleEngine::BindVertexBuffers() {
    
    BindVertexBuffers( false, true );
    
}

void CInstancedParticleEngine::BindVertexBuffers( bool genbuffer, bool bufferdata ) {
    
    if( genbuffer ) {
     
        glGenVertexArrays( 1, &m_VertexArray );
        glGenBuffers( 1, &m_InstancedBuffer );
    
    }
    
    glBindVertexArray( m_VertexArray );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_InstancedBuffer );
   
    if( bufferdata )
        glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * m_MaxParticles * 16, m_ViewMat, GL_DYNAMIC_DRAW );

    for( int j = 0; j < 4; j++ )
    {
        glEnableVertexAttribArray( j + m_ShaderOffset );
        
        glVertexAttribPointer( j + m_ShaderOffset, 4, GL_FLOAT, GL_FALSE, sizeof( float ) * 16, ( const GLvoid * )( sizeof( float ) * 4 * j ) );
        
        glVertexAttribDivisor( j + m_ShaderOffset, 1 );
        
    }
    
    if( genbuffer )
        glGenBuffers( 1, &m_InstancedRGBABuffer );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_InstancedRGBABuffer );
    
    if( bufferdata )
        glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * m_MaxParticles * 4, m_Color, GL_DYNAMIC_DRAW );
    
    glEnableVertexAttribArray( 4 + m_ShaderOffset );
    glVertexAttribPointer( 4 + m_ShaderOffset, 4, GL_FLOAT, GL_FALSE, 0, ( void * )0 );
    glVertexAttribDivisor( 4 + m_ShaderOffset, 1 );
    
    
}

void CInstancedParticleEngine::SetParticleSize( int n, float width, float height ) {
 
    m_Size[n].Set( width, height );
    
}

void CInstancedParticleEngine::SetParticleColor( int n, float r, float g, float b, float a ) {
    
    m_Color[0 + n * 4] = r;
    m_Color[1 + n * 4] = g;
    m_Color[2 + n * 4] = b;
    m_Color[3 + n * 4] = a;
    
}

void CInstancedParticleEngine::SetParticlePos( int n, float x, float y ) {
 
    CMatrix< float > mat;
    mat.Identity();
    mat.SetTranslate( x, y, 0.0f );
    mat.Scale( m_Size[n].GetX(), m_Size[n].GetY(), 1.0f );
    
    float * rawStarMat = mat.GetRawMatrix();
    
    //std::copy( rawStarMat, rawStarMat + 16, m_ViewMat + ( n * 16 ) );
    
    for( int j = 0; j < 16; j++ )
        m_ViewMat[j + n * 16] = rawStarMat[j];
    
}

void CInstancedParticleEngine::Draw() {
 
    
    glDrawElementsInstancedBaseVertex( GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, ( void * )0, m_MaxParticles, 0 );

    //Hardcoded, maybe should not be.
    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 1 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 2 );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, ( void * )0 );
    
    
}

CInstancedParticleEngine::~CInstancedParticleEngine() {

    
    glDeleteBuffers( 1, &m_InstancedBuffer );
    glDeleteBuffers( 1, &m_InstancedRGBABuffer );

    glDeleteVertexArrays( 1, &m_VertexArray );
    
    delete [] m_ViewMat;
    delete [] m_Color;
    
}