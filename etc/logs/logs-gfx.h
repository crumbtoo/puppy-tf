#ifndef LOGS_GFX_H
#define LOGS_GFX_H

#include <cjson/cJSON.h>
#include <pango/pangocairo.h>

void drawBanner(cairo_surface_t *surface, cairo_t *cr);
void drawBoard(cJSON *log, char *output_name, const char *highlight_sid3);

#endif
