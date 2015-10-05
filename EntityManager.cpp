 #include "EntityManager.h"

CEntityManager::CEntityManager( int numDrawLists ) {
 
	m_vDrawList.resize( numDrawLists );
    m_pEntContext = nullptr;

}

 CEntityManager::CEntityManager() { 
 
	m_vDrawList.resize( DRAW_DEPTH_MAX );	

}

void CEntityManager::NewEntityList( std::string entListName ) {

	m_vEntityLists.insert( std::make_pair( entListName, std::vector< CEntity * >() ) );

}

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

    std::sort( m_vDrawList[depth].begin(), m_vDrawList[depth].end(), EntPositionSort );

}

void CEntityManager::UpdateAllEntities()
{

    boost::ptr_vector< CEntityObject > * entityObjs = &m_pRawEntityList.GetEntityObjects();

	for( boost::ptr_vector< CEntityObject >::iterator i = entityObjs->begin();
		 i != entityObjs->end(); i++ )
    {

        CEntity * e = ( *i ).GetContent();

        if( e->IsActive() )
            e->Update();

        if( e->KillMe() )
            DeleteEntity( e );

    }

}


void CEntityManager::RemoveFromDrawList( CWorldEntity * ent, int depth ) {

    for( std::vector< CWorldEntity * >::iterator iter = m_vDrawList[depth].begin();
         iter != m_vDrawList[depth].end(); iter++ )
    {

        if( ( *iter )->GetGlobalCount() == ent->GetGlobalCount() )
        {

            m_vDrawList[depth].erase( iter );
            return;

        }

    }

}

void CEntityManager::UpdateDrawListLayersForEntity( CWorldEntity * ent, int depth )
{

    RemoveFromDrawList( ent, depth );

    int curdepth = ent->GetDrawDepth();
    m_vDrawList[curdepth].push_back( static_cast< CWorldEntity * >( ent ) );

}

void CEntityManager::UpdateDrawListLayers()
{

	for( int j = 0; j < m_vDrawList.size(); j++ ) {

		for( std::vector< CWorldEntity * >::iterator iter = m_vDrawList[j].begin();
				iter != m_vDrawList[j].end(); iter++ )
		{
			int depth = ( *iter )->GetDrawDepth();

			if( depth != j )
			{

				CWorldEntity * e = ( *iter );
				e->SetOldDrawDepthToNew();
				m_vDrawList[j].erase( iter );
				m_vDrawList[depth].push_back( static_cast< CWorldEntity * >( e ) );

			}

		}

	}


}

int CEntityManager::DrawAllEntitiesAtDepth( int i ) {
    
    std::vector< CWorldEntity * >::iterator iter = m_vDrawList[i].begin();
    int c = 0;
    
    for( ; iter != m_vDrawList[i].end(); iter++ )
    {
        
        CWorldEntity * e = ( *iter );
        
        if( e->IsActive() && !e->GetEntityManagerDrawOverride() ) {
            
            e->Draw();
            c++;
            
        }
            
            
    }
    
    return c;
    
}

void CEntityManager::DrawAllEntities()
{

	for( int i = 0; i < m_vDrawList.size(); i++ )
    {

        DrawAllEntitiesAtDepth( i );

    //    m_vDrawList[i].clear();


    }

}

void CEntityManager::QueueEntity( CEntity * ent ) {
    
    m_pQueuedEntities.push_back( ent );
    
}

void CEntityManager::RemoveAllQueuedEntities() {
   
    BOOST_FOREACH( CEntity * e, m_pQueuedEntities )
    {
        
        delete e;
        
    }
    
    m_pQueuedEntities.clear();
    
}

void CEntityManager::RemoveAllEntities() {
    
    boost::ptr_vector< CEntityObject > & objs = GetEntityObjects();
    boost::ptr_vector< CEntityObject >::iterator i = objs.begin();
    
    for( ; i != objs.end(); ) {
        
        CEntity * e = ( *i ).GetContent();
        RemoveEntity( e );
        
        i = objs.begin();
        
    }
    
}

void CEntityManager::AddAllQueuedEntities() {
    
    
    BOOST_FOREACH( CEntity * e, m_pQueuedEntities )
    {
        
        if( e != NULL )
            AddEntity( e );
        
    }
    
    m_pQueuedEntities.clear();
    
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
    
    for( int j = 0; j < m_pDeletedEntities.size(); j++ )
        if( m_pDeletedEntities[j]->GetGlobalCount() == pEntity->GetGlobalCount() )
            return;

    pEntity->SetActive( false );
    m_pDeletedEntities.push_back( pEntity );

}


void CEntityManager::AddEntityToList( std::string type, CEntity * ent )
{

    ent->SetBeingTracked( true );
    ent->TrackedAs( type );

    m_vEntityLists[type].push_back( ent );

}

void CEntityManager::AddEntity( CEntity * ent )
{

    m_pRawEntityList.AddEntity( ent );

    if( ent->IsDrawable() )
    {

        int depth = ent->GetDrawDepth();
        m_vDrawList[depth].push_back( static_cast< CWorldEntity * >( ent ) );

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

            for( std::vector< CEntity * >::iterator iter = m_vEntityLists[type].begin();
                 iter != m_vEntityLists[type].end(); iter++ )
            {

                if( ( *iter )->GetGlobalCount() == ent->GetGlobalCount() )
                {

                    m_vEntityLists[type].erase( iter );
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


