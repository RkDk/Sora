#include "PhysicsWorld.h"


void CPhysicsWorld::Update( int velIter, int posIter )
{

    if( m_LastIteration == 0 )
        m_LastIteration = SDL_GetTicks();

    int diff = SDL_GetTicks() - m_LastIteration;
    int itercount = ( float )diff / TIMESTEP;

    for( int j = 0; j < itercount; j++ )
    {

        m_PhysWorld.Step( TIMESTEP, velIter, posIter );

    }

    if( itercount > 0 )
        m_LastIteration = SDL_GetTicks();

}
