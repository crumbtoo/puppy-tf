#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
#include <lauxlib.h>
#include <curl/curl.h>

#include "logs-gfx.h"
#include "ints.h"

#define MAX_CURL_RETURN 256 * 256

static char *qcurl(const char *url)
{
	const char *useragent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36 Edge/18.19582";

	char *buf = calloc(MAX_CURL_RETURN + 1, 1);
	if(buf == NULL) /* malloc fail */
		return NULL;

	FILE *fp = fmemopen(buf, MAX_CURL_RETURN, "w");
	CURL *ch;

	/* init the curl session */
	ch = curl_easy_init();
	curl_global_init(CURL_GLOBAL_ALL);
 
	/* specify URL to get */
	curl_easy_setopt(ch, CURLOPT_URL, url);

	/* fix error 77 */
	curl_easy_setopt(ch, CURLOPT_SSL_VERIFYPEER, 0);
 
	/* set useragent */
	curl_easy_setopt(ch, CURLOPT_USERAGENT, useragent);

	/* write to fp (chunk in heap) */
	curl_easy_setopt(ch, CURLOPT_WRITEDATA, fp);
 
	/* call cURL */
	if(curl_easy_perform(ch) != CURLE_OK)
		return NULL;

	/* cleanup curl stuff */
	curl_easy_cleanup(ch);
	curl_global_cleanup();

	fclose(fp);

	return buf;
}

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

int luaopen_llogsTF(lua_State* L)
{
    static const struct luaL_Reg llogsTF [] =
    {
        {"renderlog", l_renderlog},
        {NULL, NULL}
    };
    luaL_register(L, "llogsTF", llogsTF);
    return 1;
}

