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
}

void parse_class_stats(tf2_player *player, cJSON *log)
{
	tf_class_stats class_stats;
	cJSON *p;
	cJSON *cstats = cJSON_GetObjectItemCaseSensitive(log, "class_stats");

	u8 cx = 0;
	const cJSON *cs = NULL;
	cJSON_ArrayForEach(cs, cstats)
	{
		p = cJSON_GetObjectItemCaseSensitive(cs, "type");
		if(cJSON_IsString(p))
		{
			

			printf("class %d: %s\n", cx, p->valuestring);
		}

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

		printf("team: %s\n", p->valuestring);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "kills");
	if(cJSON_IsNumber(p))
	{
		player.kills = p->valueint;
		printf("kills: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "deaths");
	if(cJSON_IsNumber(p))
	{
		player.deaths = p->valueint;
		printf("deaths: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "assists");
	if(cJSON_IsNumber(p))
	{
		player.assists = p->valueint;
		printf("assists: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "suicides");
	if(cJSON_IsNumber(p))
	{
		player.suicides = p->valueint;
		printf("suicides: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "kapd");
	if(cJSON_IsString(p))
	{
		/* replace with `player.kills + player.assists / player.deaths` */
		player.kapd = strtod(p->valuestring, NULL);
		printf("kapd: %f\n", strtod(p->valuestring, NULL));
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "kpd");
	if(cJSON_IsString(p))
	{
		/* replace with `player.kills + player.assists / player.deaths` */
		player.kpd = strtod(p->valuestring, NULL);
		printf("kpd: %f\n", strtod(p->valuestring, NULL));
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "dmg");
	if(cJSON_IsNumber(p))
	{
		player.dmg = p->valueint;
		printf("dmg: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "dmg_real");
	if(cJSON_IsNumber(p))
	{
		player.dmg_real = p->valueint;
		printf("dmg_real: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "dt");
	if(cJSON_IsNumber(p))
	{
		player.dt = p->valueint;
		printf("dt: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "dt_real");
	if(cJSON_IsNumber(p))
	{
		player.dt_real = p->valueint;
		printf("dt_real: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "hr");
	if(cJSON_IsNumber(p))
	{
		player.hr = p->valueint;
		printf("hr: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "dapd");
	if(cJSON_IsNumber(p))
	{
		player.dapd = p->valueint;
		printf("dapd: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "dapm");
	if(cJSON_IsNumber(p))
	{
		player.dapm = p->valueint;
		printf("dapm: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "ubers");
	if(cJSON_IsNumber(p))
	{
		player.ubers = p->valueint;
		printf("ubers: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "drops");
	if(cJSON_IsNumber(p))
	{
		player.drops = p->valueint;
		printf("drops: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "medkits");
	if(cJSON_IsNumber(p))
	{
		player.medkits = p->valueint;
		printf("medkits: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "medkits_hp");
	if(cJSON_IsNumber(p))
	{
		player.medkits_hp = p->valueint;
		printf("medkits_hp: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "backstabs");
	if(cJSON_IsNumber(p))
	{
		player.backstabs = p->valueint;
		printf("backstabs: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "headshots");
	if(cJSON_IsNumber(p))
	{
		player.headshots = p->valueint;
		printf("headshots: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "headshots_hit");
	if(cJSON_IsNumber(p))
	{
		player.headshots_hit = p->valueint;
		printf("headshots_hit: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "sentries");
	if(cJSON_IsNumber(p))
	{
		player.sentries = p->valueint;
		printf("sentries: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "heal");
	if(cJSON_IsNumber(p))
	{
		player.heal = p->valueint;
		printf("heal: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "cpc");
	if(cJSON_IsNumber(p))
	{
		player.cpc = p->valueint;
		printf("cpc: %d\n", p->valueint);
	}

	p = cJSON_GetObjectItemCaseSensitive(log, "ic");
	if(cJSON_IsNumber(p))
	{
		player.ic = p->valueint;
		printf("ic: %d\n", p->valueint);
	}

	printf("\n");
	return player;
}
