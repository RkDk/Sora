#ifndef GAMEINPUT_H_
#define GAMEINPUT_H_

#include "SDL_includes.h"


class CGameInput
{

private:

	Uint8 * m_pInputKeys;
 
    SDL_Keycode m_KeyDown;
    Uint32 m_EventType;
    
public:

	void Poll();
    int PollEvent();

	bool KeyDownOnce( SDL_Keycode i ) {

		return ( m_KeyDown == i );

	}
    
    Uint32 EventType() {
     
        return m_EventType;
        
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
