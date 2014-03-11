#include "Factory.h"

CFactoryObject::~CFactoryObject()
{

    delete m_pContent;

}
