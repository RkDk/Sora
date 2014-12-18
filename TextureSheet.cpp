#include "TextureSheet.h"

void CTextureSheet::InitPixels( int width, int height ) {
 
    m_Width = width;
    m_Height = height;
    
    m_pPixels = new GLubyte[width * height * 4];
    
}

void CTextureSheet::AddPixelData( GLubyte * pData, int x, int y, int width, int height ) {

    for( int i = 0; i < height; i++ ) {
     
        for( int j = 0; j < width; j++ ) {
         
            if( x + j < m_Width ) {
                
                int srcindex = 4 * ( j + i * width );
                int dstindex = 4 * ( ( j + x ) + ( i + y ) * m_Width );
                
                for( int o = 0; o < 4; o++ )
                    m_pPixels[dstindex + o] = pData[srcindex + o];
                
            } else
                break;
        }
      
        if( y + i >= m_Height )
            break;
        
    }
    
}

void CTextureSheet::CreateGLTexture() {
    
    glGenTextures( 1, &m_SheetTexture );
    glBindTexture( GL_TEXTURE_2D, m_SheetTexture );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_pPixels );
    
    
}

CTextureSheet::~CTextureSheet() {

    delete [] m_pPixels;
    
    glDeleteTextures( 1, &m_SheetTexture );
    
}