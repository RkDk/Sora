#include "Entity.h"

int GLOBAL_ENTITY_COUNTER = 0;


void CEntity::SetGlobalCount()
{

    m_GlobalCount = GLOBAL_ENTITY_COUNTER++;

}
