#ifndef WORLDENTITY_H_
#define WORLDENTITY_H_

#include "Vector.h"
#include "Entity.h"
#include "Sprite.h"
#include "TextureImage.h"
#include "Matrix.h"

//1 meter in Box2d = 6 pixels
//Maybe make configurable per game project?
#define BOX2D_PIXEL_MUL 6.0f
#define BOX2D_METER_MUL .1666f

class CPhysBody
{

private:

    Vector3< float > m_Size;

    b2World * m_pRefWorld
    b2Body * m_pBoxBody;
    b2Fixture * m_pBoxFixture;

public:

    void Initialize();

    CPhysBody() : m_pRefWorld( NULL ), m_pBoxBody( NULL ), m_pBoxFixture( NULL )
    {

    }

    void SetReferenceWorld( b2World * w )
    {

        m_pRefWorld = w;

    }

    void SetSize( Vector3 v )
    {

        m_Size = v;

    }

    void SetPos( float x, float y )
    {

        m_pBoxBody->SetPosition( b2Vec2( x, y ) );

    }

    b2Vec2 GetPos()
    {

        return m_pBoxBody->GetPosition();

    }

    ~CPhysBody();

};

class CWorldEntity : public CEntity
{

protected:

    CSprite m_Sprite;

    Vector3< float > m_Position;
    bool m_bPhysicsBodyInit, m_bExplicitPhysicsBodyPosSet;
    CPhysBody m_PhysicsBody;

public:

    void SetPos( Vector3< float > & v )
    {

        m_Position = v;
        m_bExplicitPhysicsBodySet = true;

    }

    void SetPos( float x, float y )
    {

        m_Position.Set( x, y );
        m_bExplicitPhysicsBodySet = true;

    }

    void SetPos( float x, float y, float z )
    {

        m_Position.Set( x, y, z );
        m_bExplicitPhysicsBodySet = true;

    }

    void SetMaterial( CTextureImage * pTexImage )
    {

        m_Sprite.SetTexture( pTexImage );

    }

    void CreatePhysicsBody( float, float );

    virtual void Update();
    virtual void Draw();

    CWorldEntity() : CEntity(), m_bPhysicsBodyInit( false ), m_bExplicitPhysicsBodyPosSet( false )
    {


    }

};

#endif
