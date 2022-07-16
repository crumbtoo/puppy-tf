#include <math.h> /* M_PI */

#include <pango/pangocairo.h>

#include "logs-tf.h"
#include "catppuccin.h"
#include "logs-parse.h"
#include "ints.h"

typedef struct 
{
	u16 width;
	u16 height;
	tf_player *players[9];
	tf_game *game;
} gfx_state;

/* void roundedRectangle(cairo_t *cr, f64 x, f64 y, f64 width, f64 height, f64 aspect) */
/* { */
/* 	f64 corner_radius = height / 10.0; */
/* 	f64 radius = corner_radius / aspect; */
/* 	f64 degrees = M_PI / 180; */

/* 	cairo_new_sub_path(cr); */
/* 	cairo_arc(cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees); */
/* 	cairo_arc(cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees); */
/* 	cairo_arc(cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees); */
/* 	cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees); */
/* 	cairo_close_path(cr); */
/* } */

void drawRedScore(gfx_state state, cairo_t *cr, f64 lb, f64 rb, f64 tb, f64 bb)
{
	PangoLayout *layout;
	PangoFontDescription *font_description;

	font_description = pango_font_description_new();
	pango_font_description_set_family(font_description, "Arial");
	pango_font_description_set_weight(font_description, PANGO_WEIGHT_BOLD);
	pango_font_description_set_absolute_size(font_description, 71 * PANGO_SCALE);

	layout = pango_cairo_create_layout(cr);
	pango_layout_set_font_description(layout, font_description);
	pango_layout_set_text(layout, "RED", -1);

	/* for centering */
	int w1, h1;
	pango_layout_get_pixel_size(layout, &w1, &h1);

	cairo_set_source_rgb(cr, CAT_ROSEWATER);
	/* center text within banner */
	cairo_move_to(cr, rb - 24 - w1, (tb + ((bb - tb) / 2)) - (h1 / 2));
	pango_cairo_show_layout(cr, layout);

	/* convert int to string */
	char score[3];
	snprintf(score, 2, "%d", state.game->red_score);
	pango_layout_set_text(layout, score, -1);

	int w2;
	pango_layout_get_pixel_size(layout, &w2, NULL);

	cairo_move_to(cr, lb + 24, (tb + ((bb - tb) / 2)) - (h1 / 2));
	pango_cairo_show_layout(cr, layout);

	g_object_unref(layout);
	pango_font_description_free(font_description);
}

void drawRedBanner(gfx_state state, cairo_t *cr, f64 x, f64 y, f64 width, f64 height, f64 aspect)
{
	f64 corner_radius = height / 10.0;
	f64 radius = corner_radius / aspect;
	f64 degrees = M_PI / 180;

	cairo_set_source_rgb(cr, 0.929, 0.529, 0.588);
	cairo_new_sub_path(cr);
	cairo_arc(cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
	cairo_arc(cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
	cairo_arc(cr, x, y + height, 0, 90 * degrees, 180 * degrees);
	cairo_arc(cr, x, y, 0, 180 * degrees, 270 * degrees);
	cairo_close_path(cr);
	cairo_fill(cr);

	drawRedScore(state, cr, x, x + width, y, y + height);
}

void drawBluScore(gfx_state state, cairo_t *cr, f64 lb, f64 rb, f64 tb, f64 bb)
{
	PangoLayout *layout;
	PangoFontDescription *font_description;

	font_description = pango_font_description_new();
	pango_font_description_set_family(font_description, "Arial");
	pango_font_description_set_weight(font_description, PANGO_WEIGHT_BOLD);
	pango_font_description_set_absolute_size(font_description, 71 * PANGO_SCALE);

	layout = pango_cairo_create_layout(cr);
	pango_layout_set_font_description(layout, font_description);
	pango_layout_set_text(layout, "BLU", -1);

	/* for centering */
	int h1;
	pango_layout_get_pixel_size(layout, NULL, &h1);

	cairo_set_source_rgb(cr, CAT_ROSEWATER);
	/* center text within banner */
	cairo_move_to(cr, lb + 24, (tb + ((bb - tb) / 2)) - (h1 / 2));
	pango_cairo_show_layout(cr, layout);

	/* convert int to string */
	char score[3];
	snprintf(score, 2, "%d", state.game->blu_score);
	pango_layout_set_text(layout, score, -1);

	int w2;
	pango_layout_get_pixel_size(layout, &w2, NULL);

	cairo_move_to(cr, rb - 24 - w2, (tb + ((bb - tb) / 2)) - (h1 / 2));
	pango_cairo_show_layout(cr, layout);

	g_object_unref(layout);
	pango_font_description_free(font_description);
}

void drawBluBanner(gfx_state state, cairo_t *cr, f64 x, f64 y, f64 width, f64 height, f64 aspect)
{
	f64 corner_radius = height / 10.0;
	f64 radius = corner_radius / aspect;
	f64 degrees = M_PI / 180;

	cairo_set_source_rgb(cr, 0.541, 0.678, 0.957);
	cairo_new_sub_path(cr);
	cairo_arc(cr, x + width, y, 0, -90 * degrees, 0 * degrees);
	cairo_arc(cr, x + width, y + height, 0, 0 * degrees, 90 * degrees);
	cairo_arc(cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
	cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
	cairo_close_path(cr);
	cairo_fill(cr);

	drawBluScore(state, cr, x, x + width, y, y + height);
}

void drawBanner(gfx_state state, cairo_surface_t *surface, cairo_t *cr)
{
	u16 banner_width = (state.width - 48) / 2;
	/* draw blue banner */
	drawBluBanner(state, cr, 24, 24, banner_width, 150, 1.5);

	/* draw red banner */
	drawRedBanner(state, cr, 24 + banner_width, 24, banner_width, 150, 1.5);
}

void drawBoard(cJSON *log)
{
	u16 width = 1490;
	/* each player row is 72px tall; 24px padding on top and bottom;
	team score banner is 150px tall */
	u16 height = (getPlayerCount(cJSON_GetObjectItemCaseSensitive(log, "players")) * 72) + 48 + 150;
	tf_game g = parse_game(log);
	gfx_state state;
	state.width = width;
	state.height = height;
	state.game = &g;

	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cairo_t *cr = cairo_create(surface);

	/* draw background */
	cairo_set_source_rgb(cr, CAT_BASE);
	cairo_paint(cr);

	drawBanner(state, surface, cr);

	cairo_destroy(cr);
	cairo_surface_write_to_png(surface, "out.png");
	cairo_surface_destroy(surface);
}
