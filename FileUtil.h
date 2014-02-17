#ifndef FILEUTIL_H_
#define FILEUTIL_H_

#include <fstream>
#include <string>

namespace FileUtil
{
	
	void AppendToFile( std::string, std::string );
	bool FileExists( std::string );
	std::string ReadContentIntoString( std::string );

};

#endif
