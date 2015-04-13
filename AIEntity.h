#ifndef AIENTITY_H_
#define AIENTITY_H_

#include "WorldEntity.h"
#include "AIController.h"

class CAIEntity : public CWorldEntity
{

protected:

    CAIController * m_pAIController;
    bool m_bAIEnabled;

public:

    CAIEntity() : CWorldEntity(), m_bAIEnabled( true ), m_pAIController( NULL )
    {

    }
    
    void SetAIEnabled( bool ai ) {
     
        m_bAIEnabled = ai;
        
    }
    
    bool IsAIEnabled() {
     
        return m_bAIEnabled;
        
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
