#ifndef LOGGING_H_
#define LOGGING_H_

#include <string>

namespace Log
{

	void SetDebugLoggingEnabled( bool );
	void Debug( std::string );

	void Log( std::string );

};

#endif
