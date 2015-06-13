#ifndef SOUNDOBJECT_H_
#define SOUNDOBJECT_H_

#include "Logging.h"
#include "fmod/include/fmod.hpp"
#include <string>

class CSoundObject { 
    
    FMOD::Sound * m_pSoundObject;
    bool m_bLoaded; 
    
public:
    
    CSoundObject() : m_bLoaded( false ) {
        
    }
    
    virtual ~CSoundObject() { 
     
        m_pSoundObject->release();
        
    }
    
    void Load( FMOD::System *, std::string, int );
    void LoadSound( FMOD::System *, std::string );
    void LoadStream( FMOD::System *, std::string );
    
    FMOD::Sound * GetSound() {
     
        return m_pSoundObject;
        
    }
    
};

#endif