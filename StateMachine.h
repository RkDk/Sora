#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "State.h"
#include "Logging.h"
#include <boost/ptr_container/ptr_map.hpp>

class CStateMachine
{

private:

    boost::ptr_map< std::string, CStateBase > m_pStates;
    CStateBase * m_pCurState;

public:

    void AddState( std::string, CStateBase *, bool );

    void AddState( std::string stateName, CStateBase * pState )
    {

        AddState( stateName, pState, false );

    }

    void SetActiveState( std::string );

    bool RunState();

    CStateMachine() : m_pCurState( NULL )
    {


    }

};

#endif
