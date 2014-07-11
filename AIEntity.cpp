#include "AIEntity.h"

void AIEntity::Update()
{

    BaseUpdate();

    if( m_pAIController )
        m_pAIController->Think();

}
