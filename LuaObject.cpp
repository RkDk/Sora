#include "LuaObject.h"

CLuaObject::CLuaObject()
{

    m_pLuaState = luaL_newstate();

    luaL_openlibs( m_pLuaState );

    CreateBaseLuaHooks();

    Log::Log( "Lua initialized" );

}

void CLuaObject::Read( const char * file )
{

    int r = luaL_dofile( m_pLuaState, file );

    if( r == 1 )
    {

        Log::Log( "ERROR loading " + std::string( file ) );
        Log::Log( lua_tostring( m_pLuaState, -1 ) );

    } else
        Log::Log( "Successfully opened lua script: " + std::string( file ) );


}

int LUA_include( lua_State * pLuaState )
{

    std::string luafile = lua_tostring( s, 1 );
    Read( luafile.c_str() );

    return 0;

}

void CLuaObject::CreateBaseLuaHooks()
{

    LuaFunction( m_pLuaState, "include", LUA_include );

}


CLuaObject::~CLuaObject()
{

    if( m_pLuaState )
        lua_close( m_pLuaState );

}
