#include "SoundFactory.h"

void CSoundFactoryObject::LoadSound( FMOD::System * pSys, std::string dir ) {

    m_pContent = new CSoundObject;
    
    if( dir.find( "mp3" ) != std::string::npos )
        m_pContent->LoadStream( pSys, dir );
    else
        m_pContent->LoadSound( pSys, dir );
        
    m_UniqueTag = dir;
    
}


void CSoundFactory::SetFMODSystem( FMOD::System * pSys ) {
 
    m_pSystem = pSys;
    
}

void CSoundFactory::NewSound( std::string dir ) {
    
    if( !m_pSystem )
        return;
    
    CSoundFactoryObject * pSoundObject = new CSoundFactoryObject;
    pSoundObject->LoadSound( m_pSystem, dir );
    AddObject( dir, pSoundObject );

}

CSoundObject * CSoundFactory::GetSound( std::string dir ) {

    return GetObjectContent( dir );
    
}

