#ifndef TRAILSEFFECT_H_
#define TRAILSEFFECT_H_

#include "FrameBuffer.h"
#include "DrawContext.h"

class CTrailsEffect {
    
private:
    
    CMatrix< float > m_CurMatrix;
    CDrawContext * m_pDrawContext;
    int m_Width, m_Height;
    float m_TrailAlpha;
    
    CFrameBufferObject m_CurFBO, m_AccumFBO, m_TempFBO;
    
public:
    
    CTrailsEffect() : m_pDrawContext( NULL ), m_Width( 0 ), m_Height( 0 ), m_TrailAlpha( 0.0f ) {
        
    }
    
    void Init( CDrawContext *, int, int, float );
    
    void Clear();
    
    void BeginDrawToCurrentBuffer();
    void EndDrawToCurrentBuffer();
    
    void BeginDrawToAccumBuffer();
    void EndDrawToAccumBuffer();
    
    void DrawCurrentBuffer();
    void DrawAccumBuffer();
    
    const CMatrix< float > & GetMatrix() {
     
        return m_CurMatrix;
        
    }
    
};

#endif
