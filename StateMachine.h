#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "State.h"
#include "Logging.h"
#include <boost/ptr_container/ptr_map.hpp>

class CStateMachine
{

private:

    boost::ptr_map< std::string, CState > m_pStates;
    CState * m_pCurState;

public:

    void AddState( std::string, CState *, bool );

    void AddState( std::string stateName, CState * pState )
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
