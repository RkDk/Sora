#include "AIEntity.h"

void CAIEntity::Update()
{

    BaseUpdate();

    if( m_pAIController && m_bAIEnabled )
        m_pAIController->Think();

}
