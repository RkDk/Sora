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

#ifndef LuaNameSpace

//Macros for defining Lua namespaces and functions.
#define LuaNameSpace( l, n ) \
        lua_getglobal( l, n ); \
        if( lua_isnil( l, -1 ) == 0 ){ lua_pushnil( l ); lua_setglobal( l, n ); lua_pop( l, 1 ); } else{ lua_pop( l, 1 ); } \
        lua_createtable( l, 0, 0 ); \
        lua_setglobal( l, n )
#define LuaNameSpaceFunction( l, n, s ) \
        lua_getglobal( l, n ); \
        lua_pushcfunction( l, LUAF_##s ); \
        lua_setfield( l, -2, #s ); \
        lua_pop( l, 1 )
#define LuaFunction( l, s ) \
        lua_pushcfunction( l, LUAF_##s ); \
        lua_setglobal( l, #s )
#define LuaCallBackFunction( f ) int LUAF_##f( lua_State * pLuaState )
#define LuaNil( l ) \
        ( lua_isnil( l, -1 ) == 0 ) ? false : true

//Auxilary lua functions
//Assumes pLuaState is defined already.

#define LArgCount() \
        lua_gettop( pLuaState )
#define LNumber( n ) \
        lua_tonumber( pLuaState, n )
#define LInteger( n ) \
        lua_tointeger( pLuaState, n )
#define LString( n ) \
        lua_tostring( pLuaState, n )

#endif


class CLuaObject
{

protected:

    lua_State * m_pLuaState;

	void CreateBaseLuaHooks();
	virtual void CreateLuaHooks() = 0;

public:


    CLuaObject();
    virtual ~CLuaObject();

    void ReadFile( const char * );

    void Initialize();

    void CallLuaFunction( const char *, const char * );

};

#endif
