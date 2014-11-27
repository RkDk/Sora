#include "Sprite.h"

void CSprite::Think()
{

    if( m_bActive )
    {

        if( SDL_GetTicks() > m_NextFrameTime )
        {

            if( ++m_CurFrameIndex >= m_pTexture->GetFrameCount() )
                m_CurFrameIndex = 0;


            m_NextFrameTime = SDL_GetTicks() + ( float )m_pTexture->GetFrameDelay( m_CurFrameIndex ) * m_Speed;

        }

    }

}

void CSprite::Draw( CDrawContext * pDrawContext, CMatrix< float > * pModelMat )
{

    if( m_pTexture )
    {

        int sx = m_Size.GetX(), sy = m_Size.GetY();
        float scx = m_Size.GetX(), scy = m_Size.GetY();
        float r, g, b, a;
        const Vector2< float > & offset = m_pTexture->GetFrameOffset( m_CurFrameIndex );

        pModelMat->Translate( offset.GetX(), offset.GetY(), 0.0f );

        pModelMat->Scale( sx, sy, 1 );
        pModelMat->Scale( scx, scy, 1.0f );
        m_pTexture->Bind( m_CurFrameIndex );
        
        m_Color.Get( &r, &g, &b, &a );
        
        pDrawContext->UpdateModelMatrix( pModelMat );
        pDrawContext->SetDrawColor( r, g, b, a );
        pDrawContext->Draw2DVertexBuffer();

    }

}
