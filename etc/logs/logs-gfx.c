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

void drawRedBanner(cairo_t *cr, f64 x, f64 y, f64 width, f64 height, f64 aspect)
{
	f64 corner_radius = height / 10.0;
	f64 radius = corner_radius / aspect;
	f64 degrees = M_PI / 180;

	cairo_new_sub_path(cr);
	cairo_arc(cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
	cairo_arc(cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
	cairo_arc(cr, x, y + height, 0, 90 * degrees, 180 * degrees);
	cairo_arc(cr, x, y, 0, 180 * degrees, 270 * degrees);
	cairo_close_path(cr);
}

void drawBluBanner(cairo_t *cr, f64 x, f64 y, f64 width, f64 height, f64 aspect)
{
	f64 corner_radius = height / 10.0;
	f64 radius = corner_radius / aspect;
	f64 degrees = M_PI / 180;

	cairo_new_sub_path(cr);
	cairo_arc(cr, x + width, y, 0, -90 * degrees, 0 * degrees);
	cairo_arc(cr, x + width, y + height, 0, 0 * degrees, 90 * degrees);
	cairo_arc(cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
	cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
	cairo_close_path(cr);
}

void drawBanner(cairo_surface_t *surface, cairo_t *cr, gfx_state state)
{
	u16 banner_width = (state.width - 48) / 2;
	/* draw blue banner */
	cairo_set_source_rgb(cr, 0.541, 0.678, 0.957);
	drawBluBanner(cr, 24, 24, banner_width, 150, 1.5);
	cairo_fill(cr);

	/* draw red banner */
	cairo_set_source_rgb(cr, 0.929, 0.529, 0.588);
	drawRedBanner(cr, 24 + banner_width, 24, banner_width, 150, 1.5);
	cairo_fill(cr);


	PangoLayout *layout;
	PangoFontDescription *font_description;

	font_description = pango_font_description_new();
	pango_font_description_set_family(font_description, "Arial");
	pango_font_description_set_weight(font_description, PANGO_WEIGHT_BOLD);
	pango_font_description_set_absolute_size(font_description, 71 * PANGO_SCALE);

	layout = pango_cairo_create_layout(cr);
	pango_layout_set_font_description(layout, font_description);
	pango_layout_set_text(layout, "BLU", -1);

	cairo_set_source_rgb(cr, CAT_ROSEWATER);
	cairo_move_to(cr, 24.0, 24.0);
	pango_cairo_show_layout(cr, layout);

	g_object_unref(layout);
	pango_font_description_free(font_description);
}

void drawBoard(cJSON *log)
{
	u16 width = 1490;
	/* each player row is 72px tall; 24px padding on top and bottom;
	team score banner is 150px tall */
	u16 height = (getPlayerCount(cJSON_GetObjectItemCaseSensitive(log, "players")) * 72) + 48 + 150;

	gfx_state state;
	state.width = width;
	state.height = height;

	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cairo_t *cr = cairo_create(surface);

	/* draw background */
	cairo_set_source_rgb(cr, CAT_BASE);
	cairo_paint(cr);

	drawBanner(surface, cr, state);

	cairo_destroy(cr);
	cairo_surface_write_to_png(surface, "out.png");
	cairo_surface_destroy(surface);
}
