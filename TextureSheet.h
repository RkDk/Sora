#ifndef TEXTURESHEET_H_
#define TEXTURESHEET_H_

#include <GL/glew.h>
#include <string>

class CTextureSheet {
  
private:
    
    GLuint m_SheetTexture;
    GLubyte * m_pPixels;
    
    int m_Width, m_Height;
    long int m_MaxIndices;
    
public:
    
    CTextureSheet() : m_pPixels( nullptr ) { }
    
    ~CTextureSheet();
    
    GLuint GetTexture() { return m_SheetTexture; }
    
    void GetSize( int * width, int * height ) {
        
        *width = m_Width;
        *height = m_Height;
        
    }
    
    void Free() {
        if( m_pPixels ) {
            delete [] m_pPixels;
            m_pPixels = nullptr;
            glDeleteTextures( 1, &m_SheetTexture );
        }
    }
    
    void InitPixels( int, int );
    void Resize( int, int );
    void CreateGLTexture();
    void AddPixelData( GLubyte *, int, int, int, int );
    void AddPixelDataLuminance( GLubyte *, int, int, int, int );
    
};

#endif
