#include "EntityManager.h"

void CEntityFactory::AddEntity( CEntity * ent )
{

    CEntityObject * entObj = new CEntityObject;
    entObj->SetTag( ent->GetUniqueID() );
    entObj->SetContent( ent );

    AddObject( entObj );

}

void CEntityManager::TrackEntity( std::string type, CEntity * ent )
{

    ent->SetBeingTracked( true );
    ent->TrackedAs( type );

    m_pTrackedEntityList[type].push_back( ent );

}

void CEntityManager::AddEntity( CEntity * ent )
{

    m_pRawEntityList.AddEntity( ent );

}

void CEntityManager::RemoveEntity( CEntity * ent )
{

    if( ent->IsBeingTracked() )
    {

        std::vector< std::string > trackedTypes = ent->GetTrackedTypes();

        for( int j = 0; j < trackedTypes.size(); j++ )
        {

            std::string type = trackedTypes[j];

            for( std::vector< CEntity * >::iterator iter = m_pTrackedEntityList[type].begin();
                 iter != m_pTrackedEntityList[type].end(); iter++ )
            {

                if( ( *iter )->GetGlobalCount() == ent->GetGlobalCount() )
                {

                    m_pTrackedEntityList[type].erase( iter );
                    break;

                }

            }

        }

    }

    m_pRawEntityList.RemoveObject( ent->GetUniqueID() );

}
