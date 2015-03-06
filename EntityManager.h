#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include "Factory.h"
#include "WorldEntity.h"
#include "Entity.h"

#define DRAW_DEPTH_MAX 10

class CEntityObject : public CFactoryObject< CEntity >
{

public:


};

class CEntityFactory : public CVectorFactory< CEntityObject, CEntity >
{

private:



public:

    void AddEntity( CEntity * );

    boost::ptr_vector< CEntityObject > & GetEntityObjects()
    {

        return m_pFactoryObjects;

    }

};

class CEntityManager
{

protected:

    CEntityFactory m_pRawEntityList;

    std::vector< CEntity * > m_pQueuedEntities;
    std::vector< CEntity * > m_pDeletedEntities;
    std::vector< CWorldEntity * > m_pDrawList[DRAW_DEPTH_MAX];
    std::map< std::string, std::vector< CEntity * > > m_pTrackedEntityList;

public:

    std::vector< CEntity * > & GetTrackedEntityList( std::string type )
    {

        return m_pTrackedEntityList[type];

    }

    boost::ptr_vector< CEntityObject >::iterator BeginIterate() {
     
        return m_pRawEntityList.GetEntityObjects().begin();
        
    }
    
    boost::ptr_vector< CEntityObject >::iterator EndIterate() {
     
        return m_pRawEntityList.GetEntityObjects().end();
        
    }
    
    
    boost::ptr_vector< CEntityObject > & GetEntityObjects()
    {

        return m_pRawEntityList.GetEntityObjects();

    }
    
    void QueueEntity( CEntity * );

    void RemoveFromDrawList( CWorldEntity *, int );
    void SortDrawEntitiesBasedOnPosition( int );
    void UpdateDrawListLayersForEntity( CWorldEntity *, int );
    void UpdateDrawListLayers();

    void TrackEntity( std::string, CEntity * );
    void AddEntity( CEntity * );

    void RemoveEntity( CEntity * );

    void RemoveAllEntities();
    void DeleteEntity( CEntity * );
    void AddAllQueuedEntities();
    void RemoveAllDeletedEntities();
    
    void DrawAllEntitiesAtDepth( int );
    void DrawAllEntities();
};

#endif
