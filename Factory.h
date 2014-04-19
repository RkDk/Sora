#ifndef FACTORY_H_
#define FACTORY_H_

#include <string>
#include <boost/ptr_container/ptr_map.hpp>

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

	virtual ~CFactoryObject()
	{

		delete m_pContent;

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
class CFactory
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

        ObjMap::iterator i = m_pFactoryObjects.find( tag );

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
