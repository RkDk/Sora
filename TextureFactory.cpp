#include "TextureFactory.h"

void CTextureFactoryObject::LoadTexture( std::string texture )
{

    m_pContent = new CTextureImage;
    m_pContent->Load( texture );
    m_UniqueTag = texture;

}

void CTextureFactory::NewTexture( std::string texture )
{

    CTextureFactoryObject * newTexture = new CTextureFactoryObject;
    newTexture->LoadTexture( texture );

    AddObject( texture, newTexture );

}
