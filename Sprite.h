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
    Vector2< float > m_Scale;
	Vector2< int > m_Size;
    CTextureImage * m_pTexture;

    Vector4< float > m_Color;
    
public:

    CSprite() : m_pTexture( NULL ), m_Speed( 1.0f ), m_CurFrameIndex( 0 ), m_NextFrameTime( 0 ), m_bActive( false ), m_Color( 1.0f, 1.0f, 1.0f, 1.0f ), m_Scale( 1.0f, 1.0f ), m_Size( 1.0f, 1.0f )
    {


    }

	bool IsSet()
	{

        return ( m_pTexture == NULL )? false : true;

	}

	bool IsOnLastFrame()
	{

	    return ( m_CurFrameIndex == m_pTexture->GetFrameCount() - 1 );

	}

    
    void SetColor( float r, float g, float b, float a ) {
     
        m_Color.Set( r, g, b, a );
        
    }
    
    void SetSpeed( float s ) {
     
        m_Speed = s;
        
        if( IsSet() ) {
         
            m_NextFrameTime = SDL_GetTicks() + ( float )m_pTexture->GetFrameDelay( m_CurFrameIndex ) * m_Speed;
            
        }
        
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
        m_NextFrameTime = SDL_GetTicks() + pTexture->GetFrameDelay( 0 ) * m_Speed;
        m_bActive = ( pTexture->GetFrameCount() > 1 ) ? true : false;
        m_pTexture = pTexture;

		int sx, sy;
        m_pTexture->GetFrameSize( m_CurFrameIndex, &sx, &sy );

		m_Size.Set( sx, sy );

    }
    
    void SetScale( float x, float y ) {
        
        m_Scale.Set( x, y );
        
    }

	void SetSize( int x, int y )
	{

		m_Size.Set( x, y );

	}

    void BindFrame( int frame = -1 ) {
        
        m_pTexture->Bind( frame == -1? m_CurFrameIndex : frame );
        
    }
    
    Vector2< float > GetRealSize( CDrawContext * pDrawContext ) {
    
        int sx = m_Size.GetX(), sy = m_Size.GetY();
        float scx = m_Scale.GetX(), scy = m_Scale.GetY();
        const Vector2< float > & scale = pDrawContext->GetGlobalScale();
        
        Vector2< float > size;
        size.Set( sx * scx * scale.GetX(), sy * scy * scale.GetY() );
        
        return size;
        
    }
    
    Vector2< float > GetScaledSize() {
        
        int sx = m_Size.GetX(), sy = m_Size.GetY();
        float scx = m_Scale.GetX(), scy = m_Scale.GetY();

        Vector2< float > size;
        size.Set( sx * scx, sy * scy );
        
        return size;
        
    }
    
	const Vector2< int > & GetSize() const
	{

		return m_Size;

	}

    void Think();
    void Draw( CDrawContext *, CMatrix< float > * );


};

#endif // SPRITE_H_
