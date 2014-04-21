#ifndef ENTITY_H_
#define ENTITY_H_

#include "EntityContext.h"

class CEntity
{

protected:

    CEntityContext * m_pContext;
    std::string m_ClassType;

public:

    std::string GetClassType()
    {

        return m_ClassType;

    }

    void SetContext( CEntityContext * c )
    {

        m_pContext = c;

    }

    CEntity() : m_ClassType( "ENTITY" )
    {


    }

};


#endif
