#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#include <GL/glew.h>
#include "Matrix.h"
#include "DrawContext.h"

class CFrameBufferObject
{
    
private:
    
    GLuint m_fboObject;
    GLuint m_fboTexture;
    
    int m_Width, m_Height;
    
public:
    
    CFrameBufferObject() : m_Width( 0 ), m_Height( 0 )
    { }
    
    ~CFrameBufferObject();
    
    void Init( int, int );
    
    
    inline void BeginDrawingToFBO()
    {
        
        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_fboObject );
        
    }
    
    void Clear() {
     
        BeginDrawingToFBO();
            glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
            glClear( GL_COLOR_BUFFER_BIT );
        EndDrawingToFBO();
        
    }
    
    inline void BindTexture()
    {
        
        glBindTexture( GL_TEXTURE_2D, m_fboTexture );
        
    }
    
    inline void EndDrawingToFBO()
    {
        
        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
        
    }
    
    void DrawTexture( CDrawContext *, CMatrix< float > *);
    
};



#endif
