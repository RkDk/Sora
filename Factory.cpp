#include "Factory.h"

template< typename T >
CFactoryObject<T>::~CFactoryObject()
{

    delete m_pContent;

}
