#include "JosnObject.h"

void JsonObject::Open( std::string file )
{

    std::string json = FileUtil::ReadContentIntoString( file );

    m_Doc.Parse( json.c_str() );

}

void JsonObject::SaveTo( std::string file )
{

    rapidjson::StringBuffer buffer;
    rapidjson::Write< rapidjson::StringBuffer > writer( buffer );
    m_Doc.Accept( writer );

    FileUtil::WriteContentToFile( file, buffer.GetString() );

}

