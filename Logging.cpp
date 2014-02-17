#include "Logging.h"

bool g_bDebugEnabled = false;

void Log::SetDebugLoggingEnabled( bool b )
{

	g_bDebugEnabled = b;

}

void Log::Debug( std::string log )
{

	if( g_bDebugEnabled )
	{

		log = "[DEBUG]" + log + "\n";
		FileUtil::AppendToFile( "log.txt", log );

	}

}

void Log::Log( std::string log )
{

	FileUtil::AppendToFile( "log.txt", log + "\n" );

}