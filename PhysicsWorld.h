#ifndef PHYSICSWORLD_H_
#define PHYSICSWORLD_H_

#include <SDL.h>
#include <Box2D/Box2D.h>

//Run physics simulation every <TIMESTEP> ms
#define TIMESTEP 16.667f
#define DEFAULT_VEL_ITERATIONS 8
#define DEFAULT_POS_ITERATIONS 3

class CPhysicsWorld
{

private:

    b2World * m_pPhysWorld;
    int m_LastIteration;

public:

    void Update( int, int );

    void Update()
    {

        Update( DEFAULT_VEL_ITERATIONS, DEFAULT_POS_ITERATIONS );

    }

    void SetContactListener( b2ContactListener * contactListener )
    {

        m_pPhysWorld->SetContactListener( contactListener );

    }

    void Initialize( float, float );

    CPhysicsWorld() : m_LastIteration( 0 )
    {

    }

	~CPhysicsWorld();

};

#endif

