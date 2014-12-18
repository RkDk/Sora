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

void CLuaObject::CallLuaFunction( const char * f, const char * n )
{

    lua_getglobal( m_pLuaState, n );

    if( !LuaNil( m_pLuaState ) )
    {

        lua_getfield( m_pLuaState, -1, f );

        if( !LuaNil( m_pLuaState ) )
        {

            if( lua_pcall( m_pLuaState, 0, 0, 0 ) > 0 )
            {

                Log::Debug( lua_tostring( m_pLuaState, -1 ) );
                lua_pop( m_pLuaState, 1 );

            }


        } else
            lua_pop( m_pLuaState, 1 );


    }

    lua_pop( m_pLuaState, 1 );

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

LuaCallBackFunction( GetTicks ) {
 
    lua_pushnumber( pLuaState, SDL_GetTicks() );
    
    return 1;
    
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
    LuaFunction( m_pLuaState, GetTicks );

}
