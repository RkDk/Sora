#ifndef ENTITY_H_
#define ENTITY_H_

#include "EntityContext.h"

class CEntity
{

protected:

    CEntityContext * m_pContext;

public:

    void SetContext( CEntityContext * c )
    {

        m_pContext = c;

    }

};


#endif
