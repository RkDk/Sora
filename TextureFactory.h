#ifndef TEXTUREFACTORY_H_
#define TEXTUREFACTORY_H_

#include "Factory.h"
#include "TextureImage.h"

class CTextureFactoryObject : public CFactoryObject< CTextureImage >
{

public:

    void LoadTexture( std::string );

};

class CTextureFactory : public CMappedFactory< CTextureFactoryObject, CTextureImage >
{

private:

public:

    void NewTexture( std::string );

};

#endif
