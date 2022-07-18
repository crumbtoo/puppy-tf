#include <stdio.h>
#include <stdlib.h>

#include <cjson/cJSON.h>
#include <pango/pangocairo.h>

#include "logs-parse.h"
#include "logs-tf.h"
#include "logs-gfx.h"

char *readtobuffer(char *filename)
{
	char *buf;
	size_t fsize;
	FILE* fp = fopen(filename, "r");

	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	buf = malloc(fsize + 1);
	fread(buf, fsize, 1, fp);
	fclose(fp);

	buf[fsize] = 0;

	return buf;
}

int main()
{
	char *buf = readtobuffer("./3222669.json");
	cJSON *log = cJSON_Parse(buf);

	drawBoard(log);

	free(buf);
	cJSON_Delete(log);
}
