#include "SoundObject.h"

void CSoundObject::Load( FMOD::System * sys, std::string dir, int params ) {

    if( m_bLoaded )
        return;
    
    m_bLoaded = true;
    
    if( sys->createSound( dir.c_str(), params, 0, &m_pSoundObject ) == FMOD_OK ) {
     
        Log::Log( "Successfully loaded sound: " + dir );
        
    } else {
     
        Log::Error( "Failed loading sound: " + dir );
        
    }
    
}

void CSoundObject::LoadStream( FMOD::System * sys, std::string dir ) {

    Load( sys, dir, FMOD_LOOP_NORMAL | FMOD_2D );
    
}


void CSoundObject::LoadSound( FMOD::System * sys, std::string dir ) {
    
    Load( sys, dir, FMOD_DEFAULT );

    
}

