#ifndef FILEUTIL_H_
#define FILEUTIL_H_

#include <fstream>
#include <string>
#include <vector>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

namespace FileUtil
{

	void WriteContentToFile( std::string, std::string );
	void AppendToFile( std::string, std::string );
	bool FileExists( std::string );
    void FindFilesInDirectory( std::string, std::vector< std::string > & );
    void FindFilesInDirectory( std::string, std::string, std::vector< std::string > &, bool );
    void FindFilesInDirectory( std::string, std::string, std::vector< std::string > &, bool, bool );
	std::string ReadContentIntoString( std::string );

};

#endif
