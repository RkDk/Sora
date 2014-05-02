#include "PhysicsWorld.h"


void CPhysicsWorld::Initialize( float x, float y )
{

	m_pPhysWorld = new b2World( b2Vec2( x, y ) );

}

CPhysicsWorld::~CPhysicsWorld()
{

	delete m_pPhysWorld;

}

void CPhysicsWorld::Update( int velIter, int posIter )
{

    if( m_LastIteration == 0 )
        m_LastIteration = SDL_GetTicks();

    int diff = SDL_GetTicks() - m_LastIteration;
    int itercount = ( float )diff / TIMESTEP;

    for( int j = 0; j < itercount; j++ )
    {

        m_pPhysWorld->Step( TIMESTEP, velIter, posIter );

    }

    if( itercount > 0 )
        m_LastIteration = SDL_GetTicks();

}
