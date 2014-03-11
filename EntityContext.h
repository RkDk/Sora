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

    CEntityContext( CGraphicsContext * GraphicsContext, CDrawContext * DrawContext ) : m_pGraphicsContext( GraphicsContext ),
                                                                                       m_pDrawContext( DrawContext )
    {

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
