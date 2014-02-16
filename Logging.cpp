#include "Logging.h"

bool g_bDebugEnabled = false;

void Log::SetDebugLoggingEnabled( bool b )
{

	g_bDebugEnabled = true;

}

void Log::Debug( std::string log )
{

	if( g_bDebugEnabled )
	{

		log = "[DEBUG]" + log;

	}

}

void Log::Log( std::string log )
{

}