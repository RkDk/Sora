#ifndef AICONTROLLER_H_
#define AICONTROLLER_H_

#include "WorldEntity.h"

class CAIController
{

protected:

    CWorldEntity * m_pTargetEntity;

public:
    
    virtual ~CAIController() { }
    
    void SetTargetEntity( CWorldEntity * pEnt )
    {

        m_pTargetEntity = pEnt;

    }

    virtual void Think() = 0;

    CAIController() : m_pTargetEntity( NULL )
    {

    }

};

template< typename T >
class CTemplateAIController : public CAIController
{
    
protected:
    
    T * m_pEntityContext;
    
public:
    
    void SetEntityContext( T * pEntityContext )
    {
        
        m_pEntityContext = pEntityContext;
        
    }
    
};

#endif
