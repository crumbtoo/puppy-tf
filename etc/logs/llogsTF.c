#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
#include <lauxlib.h>
#include <curl/curl.h>

#include "logs-gfx.h"
#include "../../deps/tbs/types.h"
#include "../qcurl.h"

static const char *getTmpDir()
{
    char *tmpdir;

    if ((tmpdir = getenv ("TEMP")) != NULL)   return tmpdir;
    if ((tmpdir = getenv ("TMP")) != NULL)    return tmpdir;
    if ((tmpdir = getenv ("TMPDIR")) != NULL) return tmpdir;

    return "/tmp";
}

static int l_renderlog(lua_State *L)
{
	const char *logno = luaL_checkstring(L, 1);
	const char *highlight = lua_tostring(L, 2);

	char tempname[32];
	strcpy(tempname, getTmpDir());
	strcat(tempname, "/llogsTF_XXXXXX");

	char log_url[64];
	strcpy(log_url, "https://logs.tf/api/v1/log/");
	strcat(log_url, logno);

	char *log_json = qcurl(log_url);

	if(log_json == NULL)
	{
		lua_pushnil(L);
		return 1;
	}

	int fd = mkstemp(tempname);

	cJSON *log = cJSON_Parse(log_json);
	cJSON *p = cJSON_GetObjectItemCaseSensitive(log, "success");
	if(cJSON_IsFalse(p))
	{
		p = cJSON_GetObjectItemCaseSensitive(log, "error");
		lua_pushnil(L);
		if(cJSON_IsString(p))
			lua_pushstring(L, p->valuestring);

		cJSON_Delete(log);
		close(fd);

		if(cJSON_IsString(p))
			return 2;
		else
			return 1;
	}

	drawBoard(log, tempname, highlight);


	free(log_json);
	cJSON_Delete(log);
	close(fd);

	char tempname_png[40];
	strcpy(tempname_png, tempname);
	strcat(tempname_png, ".png");
	rename(tempname, tempname_png);

	lua_pushstring(L, tempname_png);
	return 1;
}

static int l_getlatestlog(lua_State *L)
{
	const char *sid64 = luaL_checkstring(L, 1);
	u8 offset = lua_tonumber(L, 2);
	char url[128];

	sprintf(url, "https://logs.tf/api/v1/log?player=%s&limit=1&offset=%d", sid64, offset);
	char *buf = qcurl(url);

	if(buf == NULL)
		return 0;

	cJSON *ret = cJSON_Parse(buf);
	cJSON *p = cJSON_GetObjectItemCaseSensitive(ret, "success");

	if(cJSON_IsFalse(p))
		return 0;

	p = cJSON_GetObjectItemCaseSensitive(ret, "results");

	if(p->valueint < 1)
		return 0;


	p = cJSON_GetObjectItemCaseSensitive(ret, "logs")->child;
	p = cJSON_GetObjectItemCaseSensitive(p, "id");


	char *s = cJSON_Print(p);
	free(s);
	char itoa[16];
	sprintf(itoa, "%d", p->valueint);
	itoa[15] = 0;
	lua_pushstring(L, itoa);

	free(buf);
	cJSON_Delete(ret);

	return 1;
}

int luaopen_llogsTF(lua_State* L)
{
    static const struct luaL_Reg llogsTF [] =
    {
        {"renderlog", l_renderlog},
        {"getlatestlog", l_getlatestlog},
        {NULL, NULL}
    };
    luaL_register(L, "llogsTF", llogsTF);
    return 1;
}

