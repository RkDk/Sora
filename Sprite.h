#ifndef SPRITE_H_
#define SPRITE_H_

#include "DrawContext.h"
#include "TextureImage.h"
#include "Matrix.h"
#include "Vector.h"

class CSprite
{

private:

    bool m_bActive;
    int m_CurFrameIndex, m_NextFrameTime;
    float m_Speed;
	Vector2< int > m_Size;
    CTextureImage * m_pTexture;

public:

    CSprite() : m_pTexture( NULL ), m_Speed( 1.0f ), m_CurFrameIndex( 0 ), m_NextFrameTime( 0 ), m_bActive( false )
    {


    }

	bool IsSet()
	{

		return ( m_pTexture );

	}

	bool IsOnLastFrame()
	{

	    return ( m_CurFrameIndex == m_pTexture->GetFrameCount() - 1 );

	}

    void SetTexture( CTextureImage * pTexture )
    {

		if( !pTexture )
		{
			Log::Error( "Tried to set sprite to invalid texture" );
			return;
		}

        m_Speed = 1.0f;
        m_CurFrameIndex = 0;
        m_NextFrameTime = SDL_GetTicks() + pTexture->GetFrameDelay( 0 );
        m_bActive = ( pTexture->GetFrameCount() > 1 ) ? true : false;
        m_pTexture = pTexture;

		int sx, sy;
        m_pTexture->GetFrameSize( m_CurFrameIndex, &sx, &sy );

		m_Size.Set( sx, sy );

    }

	void SetSize( int x, int y )
	{

		m_Size.Set( x, y );

	}

	const Vector2< int > & GetSize() const
	{

		return m_Size;

	}

    void Think();
    void Draw( CDrawContext *, CMatrix< float > * );


};

#endif // SPRITE_H_
