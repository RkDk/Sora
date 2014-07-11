#ifndef ENTITY_H_
#define ENTITY_H_

#include "EntityContext.h"
#include <vector>
#include <string>

#include <boost/lexical_cast.hpp>

class CEntity
{

private:

    int m_GlobalCount;

    void SetGlobalCount();

protected:

    CEntityContext * m_pContext;
    std::string m_ClassType;

    bool m_bIsTracked;
    std::vector< std::string > m_TrackedTypes;

public:

    void SetBeingTracked( bool b )
    {

        m_bIsTracked = b;

    }

    void TrackedAs( std::string type )
    {

        m_TrackedTypes.push_back( type );

    }

    std::vector< std::string > & GetTrackedTypes()
    {

        return m_TrackedTypes;

    }

    bool IsBeingTracked()
    {

        return m_bIsTracked;

    }

    std::string SetClassType( std::string t )
    {

        m_ClassType = s;

    }

    std::string GetClassType()
    {

        return m_ClassType;

    }

    std::string GetUniqueID()
    {

        return m_ClassType + boost::lexical_cast< std::string >( m_GlobalCount );

    }

    void SetContext( CEntityContext * c )
    {

        m_pContext = c;

    }

    int GetGlobalCount()
    {

        return m_GlobalCount;

    }

    virtual void Draw()
    {


    }

    virtual void Update()
    {



    }

    CEntity() : m_ClassType( "ENTITY" ), m_bIsTracked( false ), m_GlobalCount( 0 )
    {

        SetGlobalCount();

    }

    virtual ~CEntity() { }

};


#endif
