#include <stdio.h>
#include <stdlib.h>

#include <cjson/cJSON.h>
#include <pango/pangocairo.h>

#include "logs-parse.h"
#include "logs-tf.h"
#include "logs-gfx.h"

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
	fclose(fp);
	buf[buf_cx] = 0;
	return buf;
}

int main()
{
	char *buf = readtobuffer("./3222669.json");
	cJSON *log = cJSON_Parse(buf);
	cJSON *players = cJSON_GetObjectItemCaseSensitive(log, "players");

	drawBoard(log);

	cJSON_Delete(log);
}
