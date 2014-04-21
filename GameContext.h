#ifndef GAMECONTEXT_H_
#define GAMECONTEXT_H_

#include "EntityContext.h"
#include "SDL.h"

class CGameContext : public CEntityContext
{

private:

	Uint32 m_BeginFrameTime;

public:

	void BeginFrame();
	void EndFrame();

	CGameContext() : m_BeginFrameTime( 0 ), CEntityContext()
	{
	}

};

#endif
