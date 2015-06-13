#ifndef SOUNDFACTORY_H_
#define SOUNDFACTORY_H_

#include "Factory.h"
#include "SoundObject.h"
#include <string>
#include <fmod/include/fmod.hpp>

class CSoundFactoryObject : public CFactoryObject< CSoundObject > {
    
public:
    
    void LoadSound( FMOD::System *, std::string );
    
};

class CSoundFactory : public CMappedFactory< CSoundFactoryObject, CSoundObject > {
    
private:
    
    FMOD::System * m_pSystem;
    
public:
    
    void SetFMODSystem( FMOD::System * );
    CSoundObject * GetSound( std::string );
    void NewSound( std::string );
    
    CSoundFactory() : CMappedFactory< CSoundFactoryObject, CSoundObject >(), m_pSystem( NULL ) {
        
    }
    
};

#endif