#ifndef SOUNDCONTEXT_H_
#define SOUNDCONTEXT_H_

#include <fmod/include/fmod.hpp>
#include "Logging.h"
#include "SoundObject.h"

class CSoundContext { 
    
private:
    
    FMOD::System * m_pSystem;
    
public:
    
    CSoundContext() : m_pSystem( 0 ) {
        
    }
    
    void Init( int );
    
    virtual ~CSoundContext() {
     
        m_pSystem->close();
        
    }
    
    FMOD::System * GetSystem() {
    
        return m_pSystem;
        
    }
    
    void Update() {
     
        m_pSystem->update();
        
    }
    
    FMOD::Channel * PlaySound( CSoundObject * );
    
};

#endif
