#include "SoundContext.h"

void CSoundContext::Init( int numChannels ) { 
    
    bool error = false;
    
    if( FMOD::System_Create( &m_pSystem ) != FMOD_OK ) {
     
        error = true;
        Log::Error( "Failed to create FMOD system" );
        
    }
    
    if( !error && m_pSystem->init( numChannels, FMOD_INIT_NORMAL, 0 ) != FMOD_OK ) {
     
        error = true;
        Log::Error( "Failed initializing FMOD system" );
        
    }
    
    if( !error ) {
     
        Log::Log( "Initialized FMOD system" );
        
    }
    
}

FMOD::Channel * CSoundContext::PlaySound( CSoundObject * pSound ) {

    if( !m_pSystem )
        return NULL;
    
    FMOD::Channel * pChannel;

    m_pSystem->playSound( pSound->GetSound(), 0, false, &pChannel );
    
    return pChannel; 
    
}