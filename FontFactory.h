#ifndef FONTFACTORY_H_
#define FONTFACTORY_H_

#include "Factory.h"
#include "FontMaterial.h"

#include <sstream>

class CFontFactoryObject : public CFactoryObject< CFontMaterial > {
    
public:
    
    void LoadFont( std::string, FT_Library &, int );
    
};

class CFontFactory : public CMappedFactory< CFontFactoryObject, CFontMaterial > {
    
private:
    
    FT_Library * m_pFTLib;
    
public:
    
    CFontMaterial * GetFont( std::string, int );
    
    void SetFontLibrary( FT_Library & );
    void NewFont( std::string, int );
    
};

#endif
