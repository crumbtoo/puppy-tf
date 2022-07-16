#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <cjson/cJSON.h>
#include <curl/curl.h>

#include "logs-tf.h"

tf_class idclass(char *s)
{
	/* "optimized string comparison against a fixed list of strings"
	 *
	 * :troll:
	 */
	if(s[0] == 's')
	{
		if(s[1] == 'c')
			return TF_SCOUT;
		else if(s[1] == 'o')
			return TF_SOLDIER;
		else if(s[1] == 'n')
			return TF_SNIPER;
		else if(s[1] == 'p')
			return TF_SPY;
		else
			return 10;
	}
	else if(s[0] == 'm')
		return TF_MEDIC;
	else if(s[0] == 'h')
		return TF_HEAVY;
	else if(s[0] == 'p')
		return TF_PYRO;
	else if(s[0] == 'd')
		return TF_DEMOMAN;
	else if(s[0] == 'e')
		return TF_ENGINEER;
	else
		return 10;
}

void parse_class_stats(tf_player *player, cJSON *log)
{
	cJSON *p;
	cJSON *cstats = cJSON_GetObjectItemCaseSensitive(log, "class_stats");

	u8 cx = 0;
	const cJSON *cs = NULL;
	cJSON_ArrayForEach(cs, cstats)
	{
		tf_class_stats class_stats;

		p = cJSON_GetObjectItemCaseSensitive(cs, "type");
		if(cJSON_IsString(p))
			class_stats.class = idclass(p->valuestring);

		p = cJSON_GetObjectItemCaseSensitive(cs, "kills");
		if(cJSON_IsNumber(p))
			class_stats.kills = p->valueint;

		p = cJSON_GetObjectItemCaseSensitive(cs, "total_time");
		if(cJSON_IsNumber(p))
			class_stats.total_time = p->valueint;

		cx++;
	}
}

/* `log` refers to a single player's JSON object */
tf_player parse_player(cJSON *log)
{
	tf_player player;
	cJSON *p = NULL;

	strcpy(player.sid3, log->string);

	parse_class_stats(&player, log);


	p = cJSON_GetObjectItemCaseSensitive(log, "team");
	if(cJSON_IsString(p) && (p->valuestring != NULL))
	{
		/* no reason to do a full string comparison, since team can only
		be "Red" or "Blue" */
		if(p->valuestring[0] == 'R')
			player.team = TF_RED;
		else
			player.team = TF_BLUE;
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "kills");
	if(cJSON_IsNumber(p))
		player.kills = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "deaths");
	if(cJSON_IsNumber(p))
		player.deaths = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "assists");
	if(cJSON_IsNumber(p))
		player.assists = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "suicides");
	if(cJSON_IsNumber(p))
		player.suicides = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "kapd");
	if(cJSON_IsString(p))
		player.kapd = strtod(p->valuestring, NULL);
		/* replace with `player.kills + player.assists / player.deaths` */

	p = cJSON_GetObjectItemCaseSensitive(log, "kpd");
	if(cJSON_IsString(p))
		player.kpd = strtod(p->valuestring, NULL);
		/* replace with `player.kills + player.assists / player.deaths` */

	p = cJSON_GetObjectItemCaseSensitive(log, "dmg");
	if(cJSON_IsNumber(p))
		player.dmg = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "dmg_real");
	if(cJSON_IsNumber(p))
		player.dmg_real = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "dt");
	if(cJSON_IsNumber(p))
		player.dt = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "dt_real");
	if(cJSON_IsNumber(p))
		player.dt_real = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "hr");
	if(cJSON_IsNumber(p))
		player.hr = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "as");
	if(cJSON_IsNumber(p))
		player.as = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "dapd");
	if(cJSON_IsNumber(p))
		player.dapd = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "dapm");
	if(cJSON_IsNumber(p))
		player.dapm = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "ubers");
	if(cJSON_IsNumber(p))
		player.ubers = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "drops");
	if(cJSON_IsNumber(p))
		player.drops = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "medkits");
	if(cJSON_IsNumber(p))
		player.medkits = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "medkits_hp");
	if(cJSON_IsNumber(p))
		player.medkits_hp = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "backstabs");
	if(cJSON_IsNumber(p))
		player.backstabs = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "headshots");
	if(cJSON_IsNumber(p))
		player.headshots = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "headshots_hit");
	if(cJSON_IsNumber(p))
		player.headshots_hit = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "sentries");
	if(cJSON_IsNumber(p))
		player.sentries = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "heal");
	if(cJSON_IsNumber(p))
		player.heal = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "cpc");
	if(cJSON_IsNumber(p))
		player.cpc = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "ic");
	if(cJSON_IsNumber(p))
		player.ic = p->valueint;

	return player;
}

tf_game parse_game(cJSON *log)
{
	tf_game game;
	cJSON *p = NULL;
	cJSON *t = NULL;

	/* teams:
	 *    Red:
	 *       score: X
	 *    Blue:
	 *       score: X
	 * length
	 */

	t = cJSON_GetObjectItemCaseSensitive(log, "teams");

	p = cJSON_GetObjectItemCaseSensitive(t, "Red");
	p = cJSON_GetObjectItemCaseSensitive(p, "score");
	if(cJSON_IsNumber(p))
		game.red_score = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(t, "Blue");
	p = cJSON_GetObjectItemCaseSensitive(p, "score");
	if(cJSON_IsNumber(p))
		game.blu_score = p->valueint;

	p = cJSON_GetObjectItemCaseSensitive(log, "length");
	if(cJSON_IsNumber(p))
		game.match_length = p->valueint;



	t = cJSON_GetObjectItemCaseSensitive(log, "info");

	p = cJSON_GetObjectItemCaseSensitive(t, "map");
	if(cJSON_IsString(p))
	{
		strncpy(game.map, p->valuestring, 32);
		game.map[31] = 0;
	}

	p = cJSON_GetObjectItemCaseSensitive(t, "title");
	if(cJSON_IsString(p))
	{
		strncpy(game.title, p->valuestring, 64);
		game.title[63] = 0;
	}

	p = cJSON_GetObjectItemCaseSensitive(t, "date");
	if(cJSON_IsNumber(p))
		game.date = p->valueint;


	return game;
}

u8 getPlayerCount(cJSON *players)
{
	cJSON *p = players->child;
	u8 cx = 0;
	while(p != NULL)
	{
		cx++;
		p = p->next;
	}

	return cx;
}

