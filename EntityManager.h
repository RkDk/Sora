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


};

class CEntityManager
{

private:

    CEntityFactory * m_pRawEntityList;

public:

    void AddEntity( CEntity * );

};

#endif
