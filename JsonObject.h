#ifndef JSONOBJECT_H_
#define JSONOBJECT_H_

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include "FileUtil.h"

class CJsonObject
{

private:

    rapidjson::Document m_Doc;
	
public:

    void Open( std::string );
    void SaveTo( std::string );

    rapidjson::Document & GetDocument()
    {
        return m_Doc;

    }

};

#endif // JSONOBJECT_H_
