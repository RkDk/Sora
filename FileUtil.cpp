#include "FileUtil.h"
#include "Logging.h"

bool FileUtil::FileExists( std::string dir )
{

	std::ifstream file( dir );
	return ( file );

}

void FileUtil::AppendToFile( std::string dir, std::string content )
{

	std::ofstream f( dir.c_str(), std::ios_base::app );
	f << content;
	f.close();

}

std::string FileUtil::ReadContentIntoString( std::string dir )
{

    std::ifstream f( dir.c_str() );
    std::string contents( "" );

	if( !f )
	{

		Log::Log( "Attempted to read non-existant file: " + dir );
		return "";

	}

    f.seekg( 0, std::ios_base::end );
    contents.resize( f.tellg() );
    f.seekg( 0, std::ios_base::beg );

    f.read( &contents[0], contents.length() );

    f.close();

    return contents;

}
