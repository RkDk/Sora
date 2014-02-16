#include "GameInput.h"

void CGameInput::Poll()
{

	SDL_PollEvent( &m_InputEvent );
	m_pInputKeys = const_cast< Uint8 * >( SDL_GetKeyboardState( NULL ) );

}