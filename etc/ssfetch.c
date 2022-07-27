#include <stdio.h>
#include <assert.h>

#include <ssq/a2s.h>
#include <tbs/types.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define DEFAULT_PORT 27015

/* ssfetch.fetch(string hostname, u16 port) */
static int ss_fetch(lua_State *L)
{
	const char *hostname = luaL_checkstring(L, 1);
	u16 port = lua_tonumber(L, 2);

	if(port == 0) port = DEFAULT_PORT;

	/* init ssq */
	SSQ_QUERIER *q = ssq_init();
	assert(q != NULL);

	/* 3000ms timeout */
	ssq_set_timeout(q, SSQ_TIMEOUT_RECV | SSQ_TIMEOUT_SEND, 3000);
	ssq_set_target(q, hostname, port);

	/* error handling */
    if(!ssq_ok(q))
	{
        const char *errm = ssq_errm(q);
        fprintf(stderr, "ssq_set_target: %s: %s\n", hostname, errm);

        ssq_errclr(q);
        ssq_free(q);
		return 0;
    }

	A2S_INFO *info = ssq_info(q);

	/* error handling */
	if(!ssq_ok(q))
	{
        const char *errm = ssq_errm(q);
        fprintf(stderr, "ssq_info: %s\n", errm);

        ssq_errclr(q);
        ssq_free(q);
		return 0;
    }

	const char *server_env;
	switch(info->environment)
	{
		case A2S_ENVIRONMENT_LINUX:		server_env = "linux";	break;
        case A2S_ENVIRONMENT_WINDOWS:	server_env = "windows";	break;
        case A2S_ENVIRONMENT_MAC:		server_env = "mac";		break;
        default:						server_env = "unknown";	break;
	}


	/* return lua table */

	/* t = {} */
	lua_createtable(L, 0, 4);

	/* t.name = name */
	lua_pushstring(L, "name");
	lua_pushstring(L, info->name);
	lua_settable(L, -3);

	/* t.map = map */
	lua_pushstring(L, "map");
	lua_pushstring(L, info->map);
	lua_settable(L, -3);

	lua_pushstring(L, "game");
	lua_pushstring(L, info->game);
	lua_settable(L, -3);

	lua_pushstring(L, "id");
	lua_pushnumber(L, info->id);
	lua_settable(L, -3);

	lua_pushstring(L, "playercount");
	lua_pushnumber(L, info->players);
	lua_settable(L, -3);

	lua_pushstring(L, "maxplayers");
	lua_pushnumber(L, info->max_players);
	lua_settable(L, -3);

	lua_pushstring(L, "botcount");
	lua_pushnumber(L, info->bots);
	lua_settable(L, -3);

	lua_pushstring(L, "environment");
	lua_pushstring(L, server_env);
	lua_settable(L, -3);

	lua_pushstring(L, "visiblity");
	lua_pushstring(L, (info->visibility ? "private" : "public"));
	lua_settable(L, -3);

	lua_pushstring(L, "vac");
	lua_pushstring(L, (info->vac ? "secured" : "unsecured"));
	lua_settable(L, -3);

	if(ssq_info_has_stv(info))
	{
		lua_pushstring(L, "stv_port");
		lua_pushnumber(L, info->stv_port);
		lua_settable(L, -3);

		lua_pushstring(L, "stv_name");
		lua_pushstring(L, info->stv_name);
		lua_settable(L, -3);
	}

	if(ssq_info_has_keywords(info))
	{
		lua_pushstring(L, "keywords");
		lua_pushstring(L, info->keywords);
		lua_settable(L, -3);
	}

	/* cleanup */
	ssq_info_free(info);
	ssq_free(q);

	return 1;
}

int luaopen_ssfetch(lua_State *L)
{
    static const struct luaL_Reg ssfetch[] =
    {
        {"fetch", ss_fetch},
        {NULL, NULL}
    };

    luaL_register(L, "ssfetch", ssfetch);
    return 1;
}

