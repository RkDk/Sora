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
    
    ~CTextureSheet();
    
    GLuint GetTexture() { return m_SheetTexture; }
    
    void InitPixels( int, int );
    void CreateGLTexture();
    void AddPixelData( GLubyte *, int, int, int, int );
    void AddPixelDataLuminance( GLubyte *, int, int, int, int );
    
};

#endif
