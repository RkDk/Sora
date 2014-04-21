#include "StateMachine.h"

 void CStateMachine::AddState( std::string stateName, CState * pState, bool isActive )
 {

     m_pStates.insert( stateName, pState );

     if( isActive )
        m_pCurState = pState;

 }

void CStateMachine::SetActiveState( std::string stateName )
{

    boost::ptr_map< std::string, CState >::iterator i = m_pStates.find( stateName );

    if( i != m_pStates.end() )
        m_pCurState = ( *i ).second;
    else
        Log::Log( "Failed to set active state to " + stateName );

}

bool CStateMachine::RunState()
{

    if( !m_pCurState )
        return false;

    m_pCurState->Input();
    m_pCurState->Think();
    m_pCurState->Draw();

    return m_pCurState->Continue();

}
