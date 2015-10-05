#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include "Factory.h"
#include "WorldEntity.h"
#include "Entity.h"
#include "WorldEntity.h"
#include "CollisionBody.h"
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
    
    CEntityContext * m_pEntContext;

public:
    
    void SetEntityContext( CEntityContext * e ) {
        
        m_pEntContext = e;
        
    }

    std::vector< CEntity * > & GetEntityList( std::string type )
    {

        return m_vEntityLists[type];

    }
    
    boost::ptr_vector< CEntityObject > & GetEntityObjects()
    {

        return m_pRawEntityList.GetEntityObjects();

    }
    
    template< typename T >
    T * CreateEntity( float x, float y ) {
        
        if( !m_pEntContext )
            return nullptr;
        
        T * pNewEnt = new T;
        CWorldEntity * p = static_cast< CWorldEntity * >( pNewEnt );
        
        if( p ) {
            
            p->SetContext( m_pEntContext );
            p->SetPos( x, y );
            
        }
        
        QueueEntity( p );
        
        return pNewEnt;
        
    }
    
    
    
    template< typename T >
    T * CreateEntity( float x, float y, int width, int height, bool collidebox ) {
        
        if( !m_pEntContext )
            return nullptr;
        
        T * pNewEnt = CreateEntity< T >( x, y );
        
        if( pNewEnt ) {
            
            CWorldEntity * p = static_cast< CWorldEntity * >( pNewEnt );
            
            if( p ) {
                
                p->SetScale( width, height );
                
                if( collidebox ) {
                    
                    CBoxCollisionBody * colBody = new CBoxCollisionBody;
                    colBody->SetBox( 0.0f, 0.0f, width, height );
                    p->SetCollisionBody( colBody );
                    
                }
                
            }
            
        }
        
        return pNewEnt;
        
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
