#ifndef FONTFACTORY_H_
#define FONTFACTORY_H_

#include "Factory.h"
#include "FontMaterial.h"

class CFontFactoryObject : public CFactoryObject< CFontMaterial > {
    
public:
    
    void LoadFont( std::string, FT_Library & );
    
};

class CFontFactory : public CMappedFactory< CFontFactoryObject, CFontMaterial > {
    
private:
    
    FT_Library * m_pFTLib;
    
public:
    
    void SetFontLibrary( FT_Library & );
    
    void NewFont( std::string );
    
};

#endif
