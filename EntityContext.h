#ifndef ENTITYCONTEXT_H_
#define ENTITYCONTEXT_H_

#include "DrawContext.h"
#include "GraphicsContext.h"
#include "TextureFactory.h"

class CEntityContext
{

protected:

	float m_FrameDelta;
    CGraphicsContext * m_pGraphicsContext;
    CDrawContext * m_pDrawContext;
    CTextureFactory * m_pTextureFactory;

public:

    void SetTextureFactory( CTextureFactory * pTextureFactory )
    {

        m_pTextureFactory = pTextureFactory;

    }

    void SetDrawContext( CDrawContext * pDrawContext )
    {

        m_pDrawContext = pDrawContext;

    }

    void SetGraphicsContext( CGraphicsContext * pGraphicsContext )
    {

        m_pGraphicsContext = pGraphicsContext;

    }

    CDrawContext * DrawContext()
    {

        return m_pDrawContext;

    }

    CGraphicsContext * GraphicsContext()
    {

        return m_pGraphicsContext;

    }

    CTextureFactory * TextureFactory()
    {

        return m_pTextureFactory;

    }

	virtual float GetFrameDelta()
	{

		return m_FrameDelta;

	}

	CEntityContext() : m_FrameDelta( 0.0f )
	{

	}



};

#endif
