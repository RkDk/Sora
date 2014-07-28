#include "LuaObject.h"

CLuaObject::CLuaObject()
{

    m_pLuaState = luaL_newstate();

    luaL_openlibs( m_pLuaState );

}

CLuaObject::~CLuaObject()
{

    if( m_pLuaState )
        lua_close( m_pLuaState );

}

void CLuaObject::Initialize()
{

    CreateBaseLuaHooks();
    CreateLuaHooks();

    Log::Log( "Lua Initialized" );

}

void LuaStateOpenFile( lua_State * pLuaState, const char * file )
{

    int r = luaL_dofile( pLuaState, file );

    if( r == 1 )
    {

        Log::Error( "Could not load lua script: " + std::string( file ) );
        Log::Error( lua_tostring( pLuaState, -1 ) );

    } else
        Log::Log( "Successfully opened lua script: " + std::string( file ) );

}

void CLuaObject::ReadFile( const char * file )
{

    LuaStateOpenFile( m_pLuaState, file );

}

LuaCallBackFunction( include )
{

    std::string luaFile = LString( 1 );
    LuaStateOpenFile( pLuaState, luaFile.c_str() );

    return 0;

}

void CLuaObject::CreateBaseLuaHooks()
{

    LuaFunction( m_pLuaState, include );

}
