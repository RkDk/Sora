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
    
    Vector2< float > m_Offset;
    
    float m_WidthScale, m_HeightScale;
    float m_Width, m_Height;
  
public:
    
    CFrameBufferObject() : m_Width( 0 ), m_Height( 0 ), m_WidthScale( 1.0f ), m_HeightScale( 1.0f )
    { }
    
    ~CFrameBufferObject();
    
    void Init( int, int );
    void Init( int, int, float, float );
    
    float GetOffsetX() {
     
        return m_Offset.GetX();
        
    }
    
    float GetOffsetY() {
     
        return m_Offset.GetY();
        
    }
    
    float GetWidth() {
     
        return m_Width;
        
    }
    
    float GetHeight() {
     
        return m_Height;
        
    }
    
    GLuint GetTexture() { 
     
        return m_fboTexture;
        
    }

    
    inline void BeginDrawingToFBO()
    {
        
        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, m_fboObject );
        
    }
    
    void Clear( float r, float g, float b, float a ) {
     
        BeginDrawingToFBO();
            glClearColor( r, g, b, a );
            glClear( GL_COLOR_BUFFER_BIT );
        EndDrawingToFBO();
        
    }
    
    void Clear() {
        
        Clear( 0.0f, 0.0f, 0.0f, 0.0f );
        
    }
    
    inline void BindTexture()
    {
        
        glBindTexture( GL_TEXTURE_2D, m_fboTexture );
        
    }
    
    inline void EndDrawingToFBO()
    {
        
        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
        
    }
    
    void DrawTextureDontForceSize( CDrawContext *, CMatrix< float > * );
    void DrawTexture( CDrawContext *, CMatrix< float > *, bool );
    void DrawTexture( CDrawContext *, CMatrix< float > *);
    void DrawTexture( CDrawContext * );
    void DrawTextureNoFlip( CDrawContext * );
    
};



#endif
