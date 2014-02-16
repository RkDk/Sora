#include "FileUtil.h"

std::string FileUtil::ReadContentIntoString( std::string dir )
{

    std::ifstream f( dir.c_str() );
    std::string contents( "" );
       
    f.seekg( 0, std::ios::end );
    contents.resize( f.tellg() );
    f.seekg( 0, std::ios::beg );
       
    f.read( &contents[0], contents.length() );
       
    f.close();
       
    return contents;

}