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
    int m_ClassTypeID;

    bool m_bOverrideEntityManagerDraw;
    bool m_bActive, m_bIsTracked, m_bKillMe;
    std::vector< std::string > m_TrackedTypes;

    int m_DrawDepth;

public:

    int GetDrawDepth()
    {

        return m_DrawDepth;

    }

    void SetDrawDepth( int d )
    {

        m_DrawDepth = d;

    }

    void SetBeingTracked( bool b )
    {

        m_bIsTracked = b;

    }

    void SetActive( bool b )
    {

        m_bActive = b;

    }

    bool IsActive()
    {

        return m_bActive;

    }

    bool KillMe()
    {

        return m_bKillMe;

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

    void SetClassType( std::string t )
    {

        m_ClassType = t;

    }

    std::string GetClassType()
    {

        return m_ClassType;

    }

    int GetClassTypeID()
    {

        return m_ClassTypeID;

    }

    void SetClassTypeID( int i )
    {

        m_ClassTypeID = i;

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

    bool GetEntityManagerDrawOverride()
    {

        return m_bOverrideEntityManagerDraw;

    }

    void SetEntityManagerDrawOverride( bool b )
    {

        m_bOverrideEntityManagerDraw = b;

    }

    virtual bool IsDrawable()
    {

        return false;

    }
    


    CEntity() : m_ClassType( "ENTITY" ), m_bActive( true ), m_bIsTracked( false ), m_GlobalCount( 0 ), m_ClassTypeID( 0 ), m_bOverrideEntityManagerDraw( false ), m_DrawDepth( 0 )
    {

        SetGlobalCount();

    }

    virtual ~CEntity() {
        
    
    }

};


#endif
