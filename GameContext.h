#ifndef GAMECONTEXT_H_
#define GAMECONTEXT_H_

#include "EntityContext.h"
#include "EntityManager.h"
#include "SDL.h"

class CGameContext : public CEntityContext
{

private:

	Uint32 m_BeginFrameTime;
	CEntityManager * m_pEntityManager;

public:

    void SetEntityManager( CEntityManager * pEntityManager )
    {

        m_pEntityManager = pEntityManager;

    }

    CEntityManager * EntityManager()
    {

        return m_pEntityManager;

    }

	void BeginFrame();
	void EndFrame();

	CGameContext() : m_BeginFrameTime( 0 ), CEntityContext()
	{
	}

};

#endif
