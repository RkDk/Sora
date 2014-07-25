#ifndef GAMECONTEXT_H_
#define GAMECONTEXT_H_

#include "EntityContext.h"
#include "EntityManager.h"
#include "SDL.h"

template< class T = CEntityManager>
class CGameContext : public CEntityContext
{

protected:

	Uint32 m_BeginFrameTime;
	T * m_pEntityManager;

public:

    void SetEntityManager( T * pEntityManager )
    {

        m_pEntityManager = pEntityManager;

    }

    T * EntityManager()
    {

        return m_pEntityManager;

    }


	void BeginFrame()
	{

		m_BeginFrameTime = SDL_GetTicks();

	}

	void EndFrame()
	{

		m_FrameDelta = ( SDL_GetTicks() - m_BeginFrameTime ) * .001f;

	}

	CGameContext() : m_BeginFrameTime( 0 ), CEntityContext()
	{
	}

};

#endif
