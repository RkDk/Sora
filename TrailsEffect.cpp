#include "TrailsEffect.h"

void CTrailsEffect::Init( CDrawContext * pDrawContext, int width, int height, float alpha ) {

    m_pDrawContext = pDrawContext;
    m_Width = width;
    m_Height = height;
    
    m_CurFBO.Init( width, height );
    m_AccumFBO.Init( width, height );
    m_TempFBO.Init( width, height );
    
    m_CurMatrix.Identity();
    m_CurMatrix.Translate( 0.0f, height, 0.0f );
    
    m_TrailAlpha = alpha;
    
    Clear();
    
}

void CTrailsEffect::Clear() {

    m_CurFBO.Clear();
    m_AccumFBO.Clear();
    m_TempFBO.Clear();
    
    
}

void CTrailsEffect::DrawAccumBuffer() {

    m_pDrawContext->Bind2DVertexBuffer();
    m_AccumFBO.DrawTexture( m_pDrawContext, &m_CurMatrix );
    
    
}

void CTrailsEffect::DrawCurrentBuffer() {

    m_pDrawContext->Bind2DVertexBuffer();
    m_CurFBO.DrawTexture( m_pDrawContext, &m_CurMatrix );
    
    
}

void CTrailsEffect::BeginDrawToAccumBuffer() {

    m_AccumFBO.BeginDrawingToFBO();
    
}

void CTrailsEffect::EndDrawToAccumBuffer() {
    
    m_AccumFBO.EndDrawingToFBO();
    
    m_TempFBO.BeginDrawingToFBO();
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT );
    m_pDrawContext->SetDrawColor( 1.0f, 1.0f, 1.0f, m_TrailAlpha );
    m_AccumFBO.DrawTexture( m_pDrawContext, &m_CurMatrix );
    m_TempFBO.EndDrawingToFBO();
    
    m_AccumFBO.BeginDrawingToFBO();
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT );
    m_pDrawContext->SetDrawColor( 1.0f, 1.0f, 1.0f, 1.0f );
    m_TempFBO.DrawTexture( m_pDrawContext, &m_CurMatrix );
    m_AccumFBO.EndDrawingToFBO();
    
    
}

void CTrailsEffect::BeginDrawToCurrentBuffer() {

    
    m_CurFBO.BeginDrawingToFBO();
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    
}

void CTrailsEffect::EndDrawToCurrentBuffer() {

    m_CurFBO.EndDrawingToFBO();
    
}