#include "GameInput.h"
#include <sstream>
#include "Logging.h"

CGameInput::CGameInput() {
    
    m_bShiftMod = false;
    
}

void CGameInput::Poll()
{

	m_pInputKeys = const_cast< Uint8 * >( SDL_GetKeyboardState( NULL ) );
    PollEvent();
    
}

void CGameInput::Poll2() {
    
    m_pInputKeys = const_cast< Uint8 * >( SDL_GetKeyboardState( NULL ) );
    
}

int CGameInput::PollEvent() {
    
    SDL_Event ev;
    int i  = SDL_PollEvent( &ev);
    
    m_EventType = ev.type;
    m_KeyDown = ev.key.keysym.sym;

    m_bShiftMod = ( ev.key.keysym.mod & KMOD_SHIFT );
    
    return i; 
    
}