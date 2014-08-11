#ifndef STATE_H_
#define STATE_H_

#include "GameContext.h"
#include "GraphicsContext.h"
#include "DrawContext.h"
#include "EntityManager.h"


class CStateBase
{

protected:

    bool m_bContinue, m_bInit, m_bPostInit;

public:

    virtual void Init() = 0;
    virtual void PostInit() = 0;

	virtual void Input() = 0;
	virtual void Think() = 0;
	virtual void Draw() = 0;

	virtual bool Continue() { return m_bContinue; }

	bool DidInit()
	{

	    return m_bInit;

	}

	bool DidPostInit()
	{

	    return m_bPostInit;

	}

	CStateBase() : m_bContinue( true ), m_bInit( false ), m_bPostInit( false )
	{



	}

	virtual ~CStateBase() { }

};

template< class C = CGameContext<> >
class CState : public CStateBase
{

protected:

    C * m_pGameContext;

public:

	void SetGameContext( C * pGameContext )
	{

		m_pGameContext = pGameContext;

	}

	CState() : CStateBase()
	{

	}

	virtual ~CState() { }

};

#endif
