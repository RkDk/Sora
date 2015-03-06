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
#include "SDL_includes.h"

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
#define LuaFunctionWithName( l, s, n ) \
        lua_pushcfunction( l, LUAF_##n ); \
        lua_setglobal( l, #s )
#define LuaFunctionRemove( l, s ) \
        lua_pushnil( l ); \
        lua_setglobal( l, #s )
#define LuaCallBackFunction( f ) int LUAF_##f( lua_State * pLuaState )
#define LuaNil( l ) \
        ( lua_isnil( l, -1 ) == 0 ) ? false : true
#define LUA_FUNCTION_GET_VALUE( nn, t, f, d ) \
t CLuaObject::GetLua##nn( const char * v, const char * n ) { \
    lua_getglobal( m_pLuaState, n ); \
    if( !LuaNil( m_pLuaState ) ) { \
        lua_getfield( m_pLuaState, -1, v ); \
        if( !LuaNil( m_pLuaState ) ) { \
            t ret( f( m_pLuaState, -1 ) ); \
            lua_pop( m_pLuaState, 2 ); \
            return ret; \
        } \
        lua_pop( m_pLuaState, 1 ); \
    } \
    lua_pop( m_pLuaState, 1 ); \
    return d; \
}

#define LUA_FUNCTION_SET_VALUE( nn, t, f ) \
void CLuaObject::SetLua##nn( const char * v, const char * n, t val ) { \
    lua_getglobal( m_pLuaState, n ); \
    if( !LuaNil( m_pLuaState ) ) { \
        f( m_pLuaState, val ); \
        lua_setfield( m_pLuaState, -2, v ); \
    }\
    lua_pop( m_pLuaState, 1 );\
}



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
#define LBoolean( n ) \
        lua_toboolean( pLuaState, n )

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

    void SetLuaBoolean( const char *, const char *, bool );
    void SetLuaInt( const char *, const char *, int );
    void SetLuaFloat( const char *, const char *, float );
    void SetLuaString( const char *, const char *, const char * );
    
    bool GetLuaBoolean( const char *, const char * );
    int GetLuaInt( const char *, const char * );
    float GetLuaFloat( const char *, const char * );
    std::string GetLuaString( const char *, const char * );

    
    void CallLuaFunction( const char * );
    void CallLuaFunction( const char *, const char * );

};

#endif
