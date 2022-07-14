#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <cjson/cJSON.h>
#include <curl/curl.h>

#include "logs-tf.h"

tf_class idclass(char *s)
{
	/* who even needs strcmp() */
	if(*s == 's')
	{
		if(s[1] == 'c')
			return TF_SCOUT;
		else if(s[1] == 'o')
			return TF_SOLDIER;
		else if(s[1] == 'n')
			return TF_SNIPER;
		else if(s[1] == 'p')
			return TF_SPY;
	}
	else if(*s == 'm')
		return TF_MEDIC;
	else if(*s == 'h')
		return TF_HEAVY;
	else if(*s == 'p')
		return TF_PYRO;
	else if(*s == 'd')
		return TF_DEMOMAN;
	else if(*s == 'e')
		return TF_ENGINEER;
	else
		return 10;
}

void parse_class_stats(tf2_player *player, cJSON *log)
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

tf2_player parse_player(cJSON *log)
{
	tf2_player player;
	cJSON *p = NULL;

	strcpy(player.sid3, log->string);
	printf("player: %s\n", player.sid3);


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

	printf("\n");
	return player;
}

