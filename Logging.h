#ifndef LOGGING_H_
#define LOGGING_H_

#include "FileUtil.h"
#include <string>

namespace Log
{

	void SetDebugLoggingEnabled( bool );
	void Debug( std::string );
	void Error( std::string );
	void Log( std::string );

};

#endif
