#ifndef GAMECONTEXT_H_
#define GAMECONTEXT_H_

#include "EntityContext.h"
#include "EntityManager.h"
#include "SDL.h"

class CGameContextBase : public CEntityContext
{

protected:

	Uint32 m_BeginFrameTime;

public:


    void BeginFrame();
    void EndFrame();

	CGameContextBase() : m_BeginFrameTime( 0 ), CEntityContext()
	{
	}

};

template< class E = CEntityManager >
class CGameContext : public CGameContextBase
{

protected:

	E * m_pEntityManager;

public:

    void SetEntityManager( E * pEntityManager )
    {

        m_pEntityManager = pEntityManager;

    }

    E * EntityManager()
    {

        return m_pEntityManager;

    }



};

#endif
