#ifndef FREETYPECONTEXT_H_
#define FREETYPECONTEXT_H_

#include "ft2build.h"
#include FT_FREETYPE_H

class CFreeTypeContext {

private:

    FT_Library m_FTLib;
    
public:
    
    void Init();
    
    ~CFreeTypeContext();
    
    FT_Library & GetLibrary() {
     
        return m_FTLib;
        
    }
    
};

#endif
