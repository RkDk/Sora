#ifndef STATE_H_
#define STATE_H_

#include "GameContext.h"
#include "GraphicsContext.h"
#include "DrawContext.h"
#include "EntityManager.h"

class CState
{

    CGameContext * m_pGameContext;
    bool m_bContinue;

public:

	virtual void Input() = 0;
	virtual void Think() = 0;
	virtual void Draw() = 0;

	virtual bool Continue() { return m_bContinue; }

	virtual void SetGameContext( CGameContext * pGameContext )
	{

	    m_pGameContext = pGameContext;

	}

	CState() : m_bContinue( true )
	{



	}

};

#endif
