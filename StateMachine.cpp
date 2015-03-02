#include "StateMachine.h"

 void CStateMachine::AddState( std::string stateName, CStateBase * pState, bool isActive )
 {

     m_pStates.insert( stateName, pState );

     if( isActive )
        m_pCurState = pState;

 }

void CStateMachine::SetActiveState( std::string stateName )
{

    boost::ptr_map< std::string, CStateBase >::iterator i = m_pStates.find( stateName );

    if( i != m_pStates.end() )
        m_pCurState = ( *i ).second;
    else
        Log::Error( "Failed to set active state to " + stateName );

}

void CStateMachine::ParseMessage( int msg, std::string param ) {
 
    if( msg == STATE_MSG_SWITCH ) {
     
        m_pCurState->ResetStateMessage();
        SetActiveState( param );
        m_pCurState->OnStateSwitch();
        
    }
    
}

bool CStateMachine::RunState()
{

    if( !m_pCurState )
        return false;
    
    ParseMessage( m_pCurState->GetStateMessage(), m_pCurState->GetStrStateMessageParam() );

    if( m_pCurState->DidPostInit() )
    {

        m_pCurState->Input();
        m_pCurState->Think();
        m_pCurState->Draw();

    } else if( m_pCurState->DidInit() )
    {

        m_pCurState->PostInit();
        m_pCurState->OnStateSwitch();

    } else
    {

        m_pCurState->Init();

    }

    return m_pCurState->Continue();

}
