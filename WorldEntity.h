#ifndef WORLDENTITY_H_
#define WORLDENTITY_H_

#include "Vector.h"
#include "Entity.h"
#include "Sprite.h"
#include "TextureImage.h"
#include "Matrix.h"

#include <Box2D/Box2D.h>

//10 meter in Box2d = 5 pixels
//Maybe make configurable per game project?
#define BOX2D_PIXEL_MUL .5f
#define BOX2D_METER_MUL 2.0f

class CPhysBody
{

private:

    Vector3< float > m_Size;

    b2World * m_pRefWorld;
    b2Body * m_pBoxBody;
    b2Fixture * m_pBoxFixture;

public:

    bool Initialize();

    CPhysBody() : m_pRefWorld( NULL ), m_pBoxBody( NULL ), m_pBoxFixture( NULL )
    {

    }

    void SetReferenceWorld( b2World * w )
    {

        m_pRefWorld = w;

    }

    void SetGravity( int g )
    {

        m_pBoxBody->SetGravityScale( 0 );

    }

    void SetSize( Vector3< float > v )
    {

        m_Size = v;

    }
    

    void SetPos( float x, float y )
    {

		m_pBoxBody->SetTransform( b2Vec2( x, y ), m_pBoxBody->GetAngle() );

    }

    void SetPos2( float x, float y, float w, float h )
    {

		x = ( x + w * .5f ) * BOX2D_METER_MUL;
		y = ( y + h * .5f ) * BOX2D_METER_MUL;

		SetPos( x, y );

    }

    b2Vec2 GetPos()
    {

        return m_pBoxBody->GetPosition();

    }

    void SetBodyData( void * data )
    {

        m_pBoxBody->SetUserData( data );

    }

    ~CPhysBody();

};

class CWorldEntity : public CEntity
{

protected:

    CSprite m_Sprite;

    Vector3< float > m_Position;
    bool m_bPhysicsBodyInit, m_bExplicitPhysicsBodyPosSet, m_bFollowPhysics;
    CPhysBody m_PhysicsBody;

public:

    void Displace2( float x, float y )
    {
        x *= m_pContext->GetFrameDelta();
        y *= m_pContext->GetFrameDelta();

        Displace( x, y );

    }

    void Displace( float x, float y )
    {


        m_Position.Set( m_Position.GetX() + x, m_Position.GetY() + y );
        m_bExplicitPhysicsBodyPosSet = true;

    }

    void EnablePhysicsMovement()
    {

        m_bFollowPhysics = true;

    }

    void DisablePhysicsMovement()
    {

        m_bFollowPhysics = false;

    }

    void SetGravity( int g )
    {

        m_PhysicsBody.SetGravity( 0 );

    }

    float GetX() const
    {

        return m_Position.GetX();

    }

    float GetY() const
    {

        return m_Position.GetY();

    }

    const Vector3< float > & GetPos() const
    {

        return m_Position;

    }
    
    const Vector2< int > & GetSize() const
    {
        
        return m_Sprite.GetSize();
        
    }

    void SetPos( Vector3< float > & v )
    {

        m_Position = v;
        m_bExplicitPhysicsBodyPosSet = true;

    }

    void SetPos( float x, float y )
    {

        m_Position.Set( x, y );
        m_bExplicitPhysicsBodyPosSet = true;

    }

    void SetPos( float x, float y, float z )
    {

        m_Position.Set( x, y, z );
        m_bExplicitPhysicsBodyPosSet = true;

    }

    void SetColor( float r, float g, float b, float a ) {
        
        
        m_Sprite.SetColor( r, g, b, a );
        
    }
    
    void SetScale( float x, float y ) {
     
        m_Sprite.SetScale( x, y );
        
    }
    
    void SetMaterial( CTextureImage * pTexImage )
    {

        m_Sprite.SetTexture( pTexImage );

    }

	void SetSize( int x, int y )
	{

		m_Sprite.SetSize( x, y );

	}

    void CreatePhysicsBody( b2World *, float, float );

    void UpdateSprite();
    void DrawSprite();

    void BaseUpdate();
    void BaseDraw();

    virtual void Update()
    {

        BaseUpdate();

    }

    virtual void Draw()
    {

        BaseDraw();

    }

    virtual bool IsDrawable()
    {

        return true;

    }

    CWorldEntity() : CEntity(), m_bPhysicsBodyInit( false ), m_bExplicitPhysicsBodyPosSet( false ), m_bFollowPhysics( true )
    {


    }

    virtual ~CWorldEntity() { }

};

#endif
