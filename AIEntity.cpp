#include "AIEntity.h"

void CAIEntity::Update()
{

    BaseUpdate();

    if( m_pAIController )
        m_pAIController->Think();

}
