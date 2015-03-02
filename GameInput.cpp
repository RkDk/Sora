#include "GameInput.h"

void CGameInput::Poll()
{

	m_pInputKeys = const_cast< Uint8 * >( SDL_GetKeyboardState( NULL ) );
    SDL_PollEvent( &m_InputEvent );
    
}

int CGameInput::PollEvent() {

    return SDL_PollEvent( &m_InputEvent );
    
}