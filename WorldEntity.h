#ifndef WORLDENTITY_H_
#define WORLDENTITY_H_

#include "Vector.h"
#include "Entity.h"
#include "Sprite.h"
#include "TextureImage.h"
#include "Matrix.h"

#include <Box2D/Box2D.h>

//1 meter in Box2d = 6 pixels
//Maybe make configurable per game project?
#define BOX2D_PIXEL_MUL 6.0f
#define BOX2D_METER_MUL .1666f

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

    void SetMaterial( CTextureImage * pTexImage )
    {

        m_Sprite.SetTexture( pTexImage );

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

    CWorldEntity() : CEntity(), m_bPhysicsBodyInit( false ), m_bExplicitPhysicsBodyPosSet( false ), m_bFollowPhysics( true )
    {


    }

    virtual ~CWorldEntity() { }

};

#endif
