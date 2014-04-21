#include "EntityManager.h"

void CEntityFactory::AddEntity( CEntity * ent )
{

    CEntityObject * entObj = new CEntityObject;
    entObj->SetTag( ent->GetClassType() );
    entObj->SetContent( ent );

    AddObject( entObj );

}

void CEntityManager::AddEntity( CEntity * ent )
{

    m_pRawEntityList->AddEntity( ent );

}
