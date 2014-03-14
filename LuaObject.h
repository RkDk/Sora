#ifndef LUAOBJECT_H_
#define LUAOBJECT_H_

extern "C"
{

    #include <luajit.h>
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>

}

#include "Logging.h"

#ifndef RegisterNameSpace

//Macros for defining Lua namespaces and functions.
#define LuaNameSpace( l, n ) \
        lua_getglobal( l, n ); \
        if( lua_isnil( l, -1 ) == 0 ){ lua_pushnil( l ); lua_setglobal( l, n ); lua_pop( l, 1 ); } else{ lua_pop( l, 1 ); } \
        lua_createtable( l, 0, 0 ); \
        lua_setglobal( l, n )
#define LuaNameSpaceFunction( l, n, s, f ) \
        lua_getglobal( l, n ); \
        lua_pushcfunction( l, f ); \
        lua_setfield( l, -2, s ); \
        lua_pop( l, 1 )
#define LuaFunction( l, s, f ) \
        lua_pushcfunction( l, f ); \
        lua_setglobal( l, s )

#endif


class CLuaObject
{

protected:

    lua_State * m_pLuaState;

	void CreateBaseLuaHooks();

public:

    int GetArgCount()
    {

        return lua_gettop( m_pLuaState );

    }

    float ToNumber( int n )
    {

        return lua_tonumber( m_pLuaState, n );

    }

    int ToInteger( int n )
    {

        return lua_tointeger( m_pLuaState, n );

    }

    std::string ToString( int n )
    {

        return lua_tostring( m_pLuaState, n );

    }

    CLuaObject();
    virtual ~CLuaObject();

    void Read( const char * );

};

#endif
