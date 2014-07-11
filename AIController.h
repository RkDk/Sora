#ifndef AICONTROLLER_H_
#define AICONTROLLER_H_

#include "WorldEntity.h"

class CAIController
{

protected:

    CWorldEntity * m_pTargetEntity;

public:

    void SetTargetEntity( CWorldEntity * pEnt )
    {

        m_pTargetEntity = pEnt;

    }

    virtual void Think() = 0;

    CAIController() : m_pTargetEntity( NULL )
    {

    }

};

#endif
