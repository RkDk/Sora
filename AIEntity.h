#ifndef AIENTITY_H_
#define AIENTITY_H_

#include "WorldEntity.h"
#include "AIController.h"

class CAIEntity : public CWorldEntity
{

protected:

    CAIController * m_pAIController;

public:

    CAIEntity() : CWorldEntity(), m_pAIController( NULL )
    {

    }

    void SetAIController( CAIController * pAIController )
    {

        m_pAIController = pAIController;

    }

    CAIController * GetAIController()
    {

        return m_pAIController;

    }

    virtual void Update();

    virtual ~CAIEntity()
    {

        if( m_pAIController )
            delete m_pAIController;

    }

};

#endif
