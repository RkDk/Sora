#include "GameInput.h"
#include <sstream>
#include "Logging.h"
void CGameInput::Poll()
{

	m_pInputKeys = const_cast< Uint8 * >( SDL_GetKeyboardState( NULL ) );
    PollEvent();
    
}

int CGameInput::PollEvent() {
    
    SDL_Event ev;
    int i  = SDL_PollEvent( &ev);
    
    m_EventType = ev.type;
    m_KeyDown = ev.key.keysym.sym;

    return i; 
    
}