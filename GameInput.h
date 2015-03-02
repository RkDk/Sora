#ifndef GAMEINPUT_H_
#define GAMEINPUT_H_

#include "SDL_includes.h"


class CGameInput
{

private:

	SDL_Event m_InputEvent;
	Uint8 * m_pInputKeys;

public:

	void Poll();
    int PollEvent();

	bool KeyDownOnce( int i )
	{

		return ( m_InputEvent.key.keysym.sym == i );

	}
    
    int EventType() {
     
        return m_InputEvent.type;
        
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
