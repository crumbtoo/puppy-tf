#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

#include "logs-parse.h"
#include "logs-tf.h"

char *readtobuffer(char *filename)
{
	size_t buf_cx = 0;
	size_t buf_alloc = 256;
	char *buf = malloc(256);

	FILE* fp = fopen(filename, "r");
	char c;

	if(fp != NULL)
	{
		while((c = fgetc(fp)) != EOF)
		{
			buf[buf_cx++] = c;

			if(buf_cx >= buf_alloc)
			{
				buf_alloc += 256;
				buf = realloc(buf, buf_alloc);
			}
		}
	}
	buf[buf_cx] = 0;
	return buf;
}

int main()
{
	/* tf2_player a = parse_player("{\"team\":\"Blue\",\"class_stats\":[{\"type\":\"soldier\",\"kills\":21,\"assists\":8,\"deaths\":19,\"dmg\":7093,\"weapon\":{\"quake_rl\":{\"kills\":21,\"dmg\":7093,\"avg_dmg\":59.108333333333334,\"shots\":228,\"hits\":107}},\"total_time\":1769}],\"kills\":21,\"deaths\":19,\"assists\":8,\"suicides\":0,\"kapd\":\"1.5\",\"kpd\":\"1.1\",\"dmg\":7093,\"dmg_real\":798,\"dt\":5913,\"dt_real\":690,\"hr\":3227,\"lks\":4,\"as\":1,\"dapd\":373,\"dapm\":240,\"ubers\":0,\"ubertypes\":{},\"drops\":0,\"medkits\":64,\"medkits_hp\":2374,\"backstabs\":0,\"headshots\":0,\"headshots_hit\":0,\"sentries\":0,\"heal\":0,\"cpc\":5,\"ic\":0}"); */

	printf("%d", idclass("scout"));
	printf("%d", idclass("soldier"));
	printf("%d", idclass("pyro"));
	printf("%d", idclass("demoman"));
	printf("%d", idclass("heavy"));
	printf("%d", idclass("engineer"));
	printf("%d", idclass("medic"));
	printf("%d", idclass("sniper"));
	printf("%d", idclass("spy"));
	/* char *buf = readtobuffer("./3222669.json"); */
	/* cJSON *log = cJSON_Parse(buf); */

	/* cJSON *player = cJSON_GetObjectItemCaseSensitive(log, "players")->child; */

	/* u8 i = 0; */
	/* while(player != NULL) */
	/* { */
	/* 	tf2_player p = parse_player(player); */

	/* 	player = player->next; */
	/* } */
	/* cJSON_Delete(player); */
}
