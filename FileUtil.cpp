#include "FileUtil.h"
#include "Logging.h"

bool FileUtil::FileExists( std::string dir )
{

	std::ifstream file( dir );
	return ( file.is_open() );

}

void FileUtil::AppendToFile( std::string dir, std::string content )
{

	std::ofstream f( dir.c_str(), std::ios_base::app );
	f << content;
	f.close();

}

void FileUtil::WriteContentToFile( std::string dir, std::string content )
{

    std::ofstream f( dir.c_str(), std::ios_base::trunc );
    f.write( content.c_str(), content.length() );
    f.close();

}

std::string FileUtil::ReadContentIntoString( std::string dir )
{

    std::ifstream f( dir.c_str() );
    std::string contents( "" );

	if( !f )
	{

		Log::Error( "Attempted to read non-existant file: " + dir );
		return "";

	}

    f.seekg( 0, std::ios_base::end );
    contents.resize( f.tellg() );
    f.seekg( 0, std::ios_base::beg );

    f.read( &contents[0], contents.length() );

    f.close();

    return contents;

}

void FileUtil::FindFilesInDirectory( std::string dir, std::string ext, std::vector< std::string > & fileList, bool recursive, bool includepathinfilename ) {
    
    if( dir[dir.length()-1] != '/' )
        dir = dir + '/';
    
    boost::filesystem::directory_iterator end_itr;
    for( boost::filesystem::directory_iterator i( dir ); i != end_itr; ++i )
    {
        std::string filename = i->path().filename().string();
        
        if( boost::filesystem::is_directory( i->status() ) ) {
            
            if( recursive )
                FindFilesInDirectory( dir + filename + "/", ext, fileList, recursive, includepathinfilename );
            
        } else if( ext == "" || filename.find( ext ) != std::string::npos )
            fileList.push_back( ( ( includepathinfilename )? dir : "" ) + filename );
        
        
    }
    
}


void FileUtil::FindFilesInDirectory( std::string dir, std::string ext, std::vector< std::string > & fileList, bool recursive ) {
    
    FileUtil::FindFilesInDirectory( dir, ext, fileList, recursive, false );
    
}

void FileUtil::FindFilesInDirectory( std::string dir, std::vector< std::string > & fileList ) {

    FindFilesInDirectory( dir, "", fileList , false, false );
    
}