#include "WorldEntity.h"

bool CPhysBody::Initialize()
{

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set( 0.0f, 0.0f );

	if( !m_pRefWorld )
	{

		Log::Error( "Cannot find physics body reference world" );

	} else
	{

		m_pBoxBody = m_pRefWorld->CreateBody( &bodyDef );

		float sizex = m_Size.GetX() * .5f;
		float sizey = m_Size.GetY() * .5f;

		b2PolygonShape bodyShape;
		bodyShape.SetAsBox( sizex, sizey, b2Vec2( -sizex, sizey ), 0.0f );

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &bodyShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = .5f;

		m_pBoxFixture = m_pBoxBody->CreateFixture( &fixtureDef );

		return true;

	}

	return false;

}

CPhysBody::~CPhysBody()
{
    if( m_pRefWorld && m_pBoxBody )
    {

        m_pBoxBody->DestroyFixture( m_pBoxFixture );
        m_pRefWorld->DestroyBody( m_pBoxBody );

    }

}

void CWorldEntity::CreatePhysicsBody( b2World * physWorld, float x, float y )
{

    m_PhysicsBody.SetReferenceWorld( physWorld );
    m_PhysicsBody.SetSize( Vector3< float >( x, y ) );

	if( m_PhysicsBody.Initialize() )
    {

        m_PhysicsBody.SetBodyData( ( CWorldEntity * )this );
        m_bPhysicsBodyInit = true;

    }
}

void CWorldEntity::BaseUpdate()
{

    m_Sprite.Think();

    //Either update the position of our entity depending on the physics, or update the physics body if explicitly set.
    if( m_bPhysicsBodyInit )
    {
        if( m_bExplicitPhysicsBodyPosSet || !m_bFollowPhysics )
        {

            m_PhysicsBody.SetPos( m_Position.GetX() * BOX2D_METER_MUL, -m_Position.GetY() * BOX2D_METER_MUL );
            m_bExplicitPhysicsBodyPosSet = false;

        } else
        {

            b2Vec2 pos = m_PhysicsBody.GetPos();
            m_Position.Set( pos.x * BOX2D_PIXEL_MUL, -pos.y * BOX2D_PIXEL_MUL );

        }

    }

}

void CWorldEntity::BaseDraw()
{

	if( m_Sprite.IsSet() )
	{

		CMatrix< float > mat;

		mat.Identity();
		mat.Translate( m_Position.GetX(), m_Position.GetY(), 0.0f );

		m_Sprite.Draw( m_pContext->DrawContext(), &mat );

	}

}
