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

void CSprite::Draw( CDrawContext * pDrawContext, CMatrix * pModelMat )
{

    if( m_pTexture )
    {

        int sx, sy;
        m_pTexture->GetFrameSize( m_CurFrameIndex, &sx, &sy );

        pModelMat->Scale( sx, sy, 1 );
        m_pTexture->Bind( m_CurFrameIndex );

        pDrawContext->UpdateModelMatrix( pModelMat );
        pDrawContext->Draw2DVertexBuffer();

    }

}
