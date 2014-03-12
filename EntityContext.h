#ifndef ENTITYCONTEXT_H_
#define ENTITYCONTEXT_H_

#include "DrawContext.h"
#include "GraphicsContext.h"

class CEntityContext
{

private:

    CGraphicsContext * m_pGraphicsContext;
    CDrawContext * m_pDrawContext;

public:

    void SetDrawContext( CDrawContext * pDrawContext )
    {

        m_pDrawContext = pDrawContext;

    }

    void SetGraphicsContext( CGraphicsContext * pGraphicsContext )
    {

        m_pGraphicsContext = pGraphicsContext;

    }

    CDrawContext * GetDrawContext()
    {

        return m_pDrawContext;

    }

    CGraphicsContext * GetGraphicsContext()
    {

        return m_pGraphicsContext;

    }


};

#endif
