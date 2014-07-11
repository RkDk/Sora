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

    if( m_pCurState->DidPostInit() )
    {

        m_pCurState->Input();
        m_pCurState->Think();
        m_pCurState->Draw();

    } else if( m_pCurState->DidInit() )
    {

        m_pCurState->PostInit();

    } else
    {

        m_pCurState->Init();

    }

    return m_pCurState->Continue();

}
