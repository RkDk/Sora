#ifndef ENTITYCONTEXT_H_
#define ENTITYCONTEXT_H_

#include "DrawContext.h"
#include "GraphicsContext.h"
#include "TextureFactory.h"
#include "FreeTypeContext.h"
#include "FontFactory.h"
#include "SoundFactory.h"
#include "SoundContext.h"

class CEntityContext
{

protected:

	float m_FrameDelta;
    CGraphicsContext * m_pGraphicsContext;
    CFreeTypeContext * m_pFreeTypeContext;
    CSoundContext * m_pSoundContext;
    CDrawContext * m_pDrawContext;
    CFontFactory * m_pFontFactory;
    CSoundFactory * m_pSoundFactory;
    CTextureFactory * m_pTextureFactory;

public:
 
    int GetWindowWidth() {
     
        return m_pGraphicsContext->GetWindowWidth();
        
    }
    
    int GetWindowHeight() {
     
        return m_pGraphicsContext->GetWindowHeight();
        
    }
    
    void LoadResources( std::string );
    
    void SetSoundFactory( CSoundFactory * pSoundFactory ) { 
     
        m_pSoundFactory = pSoundFactory;
        
    }
    
    void SetSoundContext( CSoundContext * pSoundContext ) {
     
        m_pSoundContext = pSoundContext;
        
    }
    
    void SetFontFactory( CFontFactory * pFontFactory ) {
     
        m_pFontFactory = pFontFactory;
        
    }

    void SetTextureFactory( CTextureFactory * pTextureFactory )
    {

        m_pTextureFactory = pTextureFactory;

    }

    void SetFTContext( CFreeTypeContext * pFreeTypeContext ) {
     
        m_pFreeTypeContext = pFreeTypeContext;
        
    }
    
    void SetDrawContext( CDrawContext * pDrawContext )
    {

        m_pDrawContext = pDrawContext;

    }

    void SetGraphicsContext( CGraphicsContext * pGraphicsContext )
    {

        m_pGraphicsContext = pGraphicsContext;

    }
    
    CSoundContext * SoundContext() {
     
        return m_pSoundContext;
        
    }

    CDrawContext * DrawContext()
    {

        return m_pDrawContext;

    }
    
    CFreeTypeContext * FTContext() {
     
        return m_pFreeTypeContext;
        
    }

    CGraphicsContext * GraphicsContext()
    {

        return m_pGraphicsContext;

    }
    
    CSoundFactory * SoundFactory() {
     
        return m_pSoundFactory;
        
    }
    
    CFontFactory * FontFactory() {
     
        return m_pFontFactory;
        
    }

    CTextureFactory * TextureFactory()
    {

        return m_pTextureFactory;

    }

	virtual float GetFrameDelta()
	{

		return m_FrameDelta;

	}
    
    CTextureImage * GetTexture( std::string t ) {
     
        return m_pTextureFactory->GetObjectContent( t );
        
    }
    
    CFontMaterial * GetFont( std::string t, int s ) {
     
        return m_pFontFactory->GetFont( t, s );
        
    }
    
    virtual bool GetBoolean( std::string b ) = 0;

	virtual void HandleEntityContact( void * pEntityA, int entTypeA, void * pEntityB, int entTypeB )
	{


	}

	CEntityContext() : m_FrameDelta( 0.0f )
	{

	}



};

#endif
