#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include "Factory.h"
#include "Entity.h"

class CEntityObject : public CFactoryObject< CEntity >
{

public:


};

class CEntityFactory : public CVectorFactory< CEntityObject, CEntity >
{

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

    CEntityFactory * m_pRawEntityList;

    std::map< std::string, std::vector< CEntity * > > m_pTrackedEntityList;

public:

    std::vector< CEntity * > & GetTrackedEntityList( std::string type )
    {

        return m_pTrackedEntityList[type];

    }

    boost::ptr_vector< CEntityObject > & GetEntityObjects()
    {

        return m_pRawEntityList->GetEntityObjects();

    }

    void TrackEntity( std::string, CEntity * );
    void AddEntity( CEntity * );
    void RemoveEntity( CEntity * );

};

#endif
