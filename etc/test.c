#include <stdio.h>
#include <stdlib.h>

#include <cjson/cJSON.h>
#include <pango/pangocairo.h>

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
	char *buf = readtobuffer("./3222669.json");
	cJSON *log = cJSON_Parse(buf);

	cJSON *player = cJSON_GetObjectItemCaseSensitive(log, "players")->child;

	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, )
	cairo_t *cr = cairo_create(surface);

	u8 i = 0;
	while(player != NULL)
	{
		tf2_player p = parse_player(player);

		player = player->next;
	}
	cJSON_Delete(player);
}
