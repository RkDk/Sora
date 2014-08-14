#include "JsonObject.h"

void CJsonObject::Open( std::string file )
{

    std::string json = FileUtil::ReadContentIntoString( file );

    m_Doc.Parse( json.c_str() );

}

void CJsonObject::SaveTo( std::string file )
{

    rapidjson::StringBuffer buffer;
    rapidjson::Writer< rapidjson::StringBuffer > writer( buffer );
    m_Doc.Accept( writer );

    FileUtil::WriteContentToFile( file, buffer.GetString() );

}

