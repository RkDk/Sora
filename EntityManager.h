#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include "Factory.h"
#include "WorldEntity.h"
#include "Entity.h"
#include <unordered_map>

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
    std::vector< std::vector< CWorldEntity * > > m_vDrawList;
    std::unordered_map< std::string, std::vector< CEntity * > > m_vEntityLists;

public:

    std::vector< CEntity * > & GetEntityList( std::string type )
    {

        return m_vEntityLists[type];

    }
    
    boost::ptr_vector< CEntityObject > & GetEntityObjects()
    {

        return m_pRawEntityList.GetEntityObjects();

    }
    
    void QueueEntity( CEntity * );

	void UpdateAllEntities();

    void RemoveFromDrawList( CWorldEntity *, int );
    void SortDrawEntitiesBasedOnPosition( int );
    void UpdateDrawListLayersForEntity( CWorldEntity *, int );
    void UpdateDrawListLayers();

	void NewEntityList( std::string );
    void AddEntityToList( std::string, CEntity * );
    
	void AddEntity( CEntity * );

    void RemoveEntity( CEntity * );
    void RemoveAllEntities();
    
	void AddAllQueuedEntities();
	void RemoveAllQueuedEntities();

	void DeleteEntity( CEntity * );
    void RemoveAllDeletedEntities();
    
    int DrawAllEntitiesAtDepth( int );
    void DrawAllEntities();

	CEntityManager( int );
	CEntityManager();
};

#endif
