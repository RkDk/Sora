#ifndef FACTORY_H_
#define FACTORY_H_

#include <string>
#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

template< typename T >
class CFactoryObject
{

protected:

    T * m_pContent;

    std::string m_UniqueTag;

public:

    CFactoryObject() : m_pContent( NULL ), m_UniqueTag( "" )
    {

    }
    
    virtual void OnRelease() {
        
    }

	virtual ~CFactoryObject()
	{

        OnRelease();
		delete m_pContent;

	}

    void SetContent( T * content )
    {

        m_pContent = content;

    }

    T * GetContent()
    {

        return m_pContent;

    }

    void SetTag( std::string tag )
    {

        m_UniqueTag = tag;

    }

    std::string GetTag()
    {

        return m_UniqueTag;

    }

};

template< typename T, typename P >
class CVectorFactory
{

protected:

    typedef boost::ptr_vector< T > ObjMap;
    ObjMap m_pFactoryObjects;

public:

    void AddObject( T * object )
    {

        m_pFactoryObjects.push_back( object );

    }

    T * GetObject( int i )
    {

        return m_pFactoryObjects.at( i );

    }

    T * GetObject( std::string tag )
    {
        
        T * obj = NULL;

        BOOST_FOREACH( obj, m_pFactoryObjects )
        {

            if( obj->GetTag() == tag )
                return obj;

        }

        return NULL;

    }

    P * GetObjectContent( int i )
    {

        T * FactoryObject = GetObject( i );

        if( FactoryObject )
            return FactoryObject->GetContent();

        return NULL;

    }

    P * GetObjectContent( std::string tag )
    {

        T * FactoryObject = GetObject( tag );

        if( FactoryObject )
            return FactoryObject->GetContent();

        return NULL;

    }

    void RemoveObject( std::string tag )
    {

        typename ObjMap::iterator i = m_pFactoryObjects.begin();

        for( ; i != m_pFactoryObjects.end(); i++ )
        {

            if( ( *i ).GetTag() == tag )
            {

                m_pFactoryObjects.erase( i );
                return;

            }

        }

    }


};

template< typename T, typename P >
class CMappedFactory
{

protected:

    typedef boost::ptr_map< std::string, T > ObjMap;
    ObjMap m_pFactoryObjects;

public:

    void AddObject( std::string tag, T * object )
    {

        m_pFactoryObjects.insert( tag, object );

    }

    T * GetObject( std::string tag )
    {

        typename ObjMap::iterator i = m_pFactoryObjects.find( tag );

        if( i != m_pFactoryObjects.end() )
            return ( *i ).second;

        return NULL;

    }

    P * GetObjectContent( std::string tag )
    {

        T * FactoryObject = GetObject( tag );

        if( FactoryObject )
            return FactoryObject->GetContent();

        return NULL;

    }

    void RemoveObject( std::string tag )
    {

        m_pFactoryObjects.erase( tag );

    }


};

#endif
