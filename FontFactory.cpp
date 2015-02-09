#include "FontFactory.h"

void CFontFactoryObject::LoadFont( std::string dir, FT_Library & ftLib, int fontsize ) {

    m_pContent = new CFontMaterial;
    m_pContent->Load( dir, ftLib, fontsize );

    m_UniqueTag = dir;
    
}

CFontMaterial * CFontFactory::GetFont( std::string dir, int fontsize ) {
 
    std::stringstream fontname;
    fontname << dir << "_" << fontsize;
    
    return GetObjectContent( fontname.str() );
    
}

void CFontFactory::NewFont( std::string dir, int fontsize ) {

    CFontFactoryObject * newFont = new CFontFactoryObject;
    newFont->LoadFont( dir, *m_pFTLib, fontsize );

    std::stringstream fontname;
    fontname << dir << "_" << fontsize;
    
    AddObject( fontname.str(), newFont );
    
}

void CFontFactory::SetFontLibrary( FT_Library & ftLib ) {

    m_pFTLib = &ftLib;
    
}