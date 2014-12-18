#ifndef TEXTURESHEET_H_
#define TEXTURESHEET_H_

#include <GL/glew.h>

class CTextureSheet {
  
private:
    
    GLuint m_SheetTexture;
    GLubyte * m_pPixels;
    
    int m_Width, m_Height;
    
public:
    
    ~CTextureSheet();
    
    GLuint GetTexture() { return m_SheetTexture; }
    
    void InitPixels( int, int );
    void CreateGLTexture();
    void AddPixelData( GLubyte *, int, int, int, int );
    
};

#endif
