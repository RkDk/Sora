#ifndef GAMEINPUT_H_
#define GAMEINPUT_H_

#include "SDL.h"

class CGameInput
{

private:

	SDL_Event m_InputEvent;
	Uint8 * m_pInputKeys;

public:

	void Poll();

	bool InitialKeyDown( int i )
	{

		return ( m_InputEvent.key.keysym.sym == i );

	}

	bool KeyDown( int i )
	{

		return ( m_pInputKeys[i] );

	}

	bool KeyUp( int i )
	{

		return ( m_pInputKeys[i] );

	}

};

#endif
