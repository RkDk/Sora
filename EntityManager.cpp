 #include "EntityManager.h"

void CEntityFactory::AddEntity( CEntity * ent )
{

    CEntityObject * entObj = new CEntityObject;
    entObj->SetTag( ent->GetUniqueID() );
    entObj->SetContent( ent );

    AddObject( entObj );

}

bool EntPositionSort( const CWorldEntity * l, const CWorldEntity * r )
{

    return ( l->GetY() < r->GetY() );

}

void CEntityManager::SortDrawEntitiesBasedOnPosition( int depth )
{

    std::sort( m_pDrawList[depth].begin(), m_pDrawList[depth].end(), EntPositionSort );

}

void CEntityManager::RemoveFromDrawList( CWorldEntity * ent, int depth )
{

    for( std::vector< CWorldEntity * >::iterator iter = m_pDrawList[depth].begin();
         iter != m_pDrawList[depth].end(); iter++ )
    {

        if( ( *iter )->GetGlobalCount() == ent->GetGlobalCount() )
        {

            m_pDrawList[depth].erase( iter );
            return;

        }

    }

}

void CEntityManager::UpdateDrawListLayersForEntity( CWorldEntity * ent, int depth )
{

    RemoveFromDrawList( ent, depth );

    int curdepth = ent->GetDrawDepth();
    m_pDrawList[curdepth].push_back( static_cast< CWorldEntity * >( ent ) );

}

void CEntityManager::UpdateDrawListLayers()
{

    for( int j = 0; j < DRAW_DEPTH_MAX; j++ )
    {

        for( std::vector< CWorldEntity * >::iterator iter = m_pDrawList[j].begin();
             iter != m_pDrawList[j].end(); iter++ )
        {
            int depth = ( *iter )->GetDrawDepth();

            if( depth != j )
            {

                m_pDrawList[j].erase( iter );
                m_pDrawList[depth].push_back( ( *iter) );

            }

        }

    }

}

void CEntityManager::DrawAllEntities()
{

	for( int i = 0; i < DRAW_DEPTH_MAX; i++ )
    {

        std::vector< CWorldEntity * >::iterator iter = m_pDrawList[i].begin();

        for( ; iter != m_pDrawList[i].end(); iter++ )
        {

            CWorldEntity * e = ( *iter );

            if( e->IsActive() && !e->GetEntityManagerDrawOverride() )
                e->Draw();

        }

    //    m_pDrawList[i].clear();


    }

}

void CEntityManager::RemoveAllDeletedEntities()
{

    BOOST_FOREACH( CEntity * e, m_pDeletedEntities )
    {

        RemoveEntity( e );

    }

    m_pDeletedEntities.clear();

}

void CEntityManager::DeleteEntity( CEntity * pEntity )
{

    pEntity->SetActive( false );
    m_pDeletedEntities.push_back( pEntity );

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

    if( ent->IsDrawable() )
    {

        int depth = ent->GetDrawDepth();
        m_pDrawList[depth].push_back( static_cast< CWorldEntity * >( ent ) );

    }

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

    if( ent->IsDrawable() )
    {
        
        CWorldEntity * wEnt = ( CWorldEntity * )ent;

        int depth = ent->GetDrawDepth();
        RemoveFromDrawList( wEnt, depth );

    }

    m_pRawEntityList.RemoveObject( ent->GetUniqueID() );

}


