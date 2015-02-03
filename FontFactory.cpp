#include "FontFactory.h"

void CFontFactoryObject::LoadFont( std::string dir, FT_Library & ftLib ) {

    m_pContent = new CFontMaterial;
    m_pContent->Load( dir, ftLib );
    
    m_UniqueTag = dir;
    
}

void CFontFactory::NewFont( std::string dir ) {

    CFontFactoryObject * newFont = new CFontFactoryObject;
    newFont->LoadFont( dir, *m_pFTLib );
    
    AddObject( dir, newFont );
    
}

void CFontFactory::SetFontLibrary( FT_Library & ftLib ) {

    m_pFTLib = &ftLib;
    
}