#ifndef PHYSICSWORLD_H_
#define PHYSICSWORLD_H_

//Run physics simulation every <TIMESTEP> ms
#define TIMESTEP 16.667f
#define DEFAULT_VEL_ITERATIONS 8
#define DEFAULT_POS_ITERATIONS 3

class CPhysicsWorld
{

private:

    b2World m_PhysWorld;
    int m_LastIteration;

public:

    void Update( int, int );

    void Update()
    {

        Update( DEFAULT_VEL_ITERATIONS, DEFAULT_POS_ITERATIONS );

    }

    void SetGravitySpeed( float x, float y )
    {

        b2Vec2 gravSpeed( x, y );
        m_PhysWorld.SetGravity( gravSpeed );

    }

    CPhysicsWorld() : m_LastIteration( 0 )
    {

    }

};

#endif

