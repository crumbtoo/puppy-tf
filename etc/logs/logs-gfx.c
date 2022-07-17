#include <math.h> /* M_PI */
#include <stdbool.h>

#include <pango/pangocairo.h>

#include "logs-tf.h"
#include "catppuccin.h"
#include "logs-parse.h"
#include "ints.h"

typedef struct 
{
	u16 width;
	u16 height;
	u8 padding;
} gfx_state;

static void drawRedScore(gfx_state state, cairo_t *cr, f64 lb, f64 rb, f64 tb, f64 bb, u8 score)
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

	cairo_set_source_rgb(cr, CAT_TEXT);
	/* center text within banner */
	cairo_move_to(cr, rb - state.padding - w1, (tb + ((bb - tb) / 2)) - (h1 / 2));
	pango_cairo_show_layout(cr, layout);

	/* convert int to string */
	char buf[3];
	snprintf(buf, 2, "%d", score);
	pango_layout_set_text(layout, buf, -1);

	int w2;
	pango_layout_get_pixel_size(layout, &w2, NULL);

	cairo_move_to(cr, lb + state.padding, (tb + ((bb - tb) / 2)) - (h1 / 2));
	pango_cairo_show_layout(cr, layout);

	g_object_unref(layout);
	pango_font_description_free(font_description);
}

static void drawRedBanner(gfx_state state, cairo_t *cr, f64 x, f64 y, f64 width, f64 height, u8 score)
{
	f64 corner_radius = height / 10.0;
	f64 radius = corner_radius / 1.5;
	f64 degrees = M_PI / 180;

	cairo_set_source_rgb(cr, 0.929, 0.529, 0.588);
	cairo_set_source_rgb(cr, CAT_EXTERN_RED);
	cairo_new_sub_path(cr);
	cairo_arc(cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
	cairo_arc(cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
	cairo_arc(cr, x, y + height, 0, 90 * degrees, 180 * degrees);
	cairo_arc(cr, x, y, 0, 180 * degrees, 270 * degrees);
	cairo_close_path(cr);
	cairo_fill(cr);

	drawRedScore(state, cr, x, x + width, y, y + height, score);
}

static void drawBluScore(gfx_state state, cairo_t *cr, f64 lb, f64 rb, f64 tb, f64 bb, u8 score)
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

	cairo_set_source_rgb(cr, CAT_TEXT);
	/* center text within banner */
	cairo_move_to(cr, lb + state.padding, (tb + ((bb - tb) / 2)) - (h1 / 2));
	pango_cairo_show_layout(cr, layout);

	/* convert int to string */
	char buf[3];
	snprintf(buf, 2, "%d", score);
	pango_layout_set_text(layout, buf, -1);

	int w2;
	pango_layout_get_pixel_size(layout, &w2, NULL);

	cairo_move_to(cr, rb - state.padding - w2, (tb + ((bb - tb) / 2)) - (h1 / 2));
	pango_cairo_show_layout(cr, layout);

	g_object_unref(layout);
	pango_font_description_free(font_description);
}

static void drawBluBanner(gfx_state state, cairo_t *cr, f64 x, f64 y, f64 width, f64 height, u8 score)
{
	f64 corner_radius = height / 10.0;
	f64 radius = corner_radius / 1.5;
	f64 degrees = M_PI / 180;

	cairo_set_source_rgb(cr, CAT_EXTERN_BLUE);
	cairo_new_sub_path(cr);
	cairo_arc(cr, x + width, y, 0, -90 * degrees, 0 * degrees);
	cairo_arc(cr, x + width, y + height, 0, 0 * degrees, 90 * degrees);
	cairo_arc(cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
	cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
	cairo_close_path(cr);
	cairo_fill(cr);

	drawBluScore(state, cr, x, x + width, y, y + height, score);
}

void drawBanner(gfx_state state, cairo_t *cr, u8 blu_score, u8 red_score)
{
	u16 banner_width = (state.width - 48) >> 1;
	/* draw blue banner */
	drawBluBanner(state, cr, state.padding, state.padding, banner_width, 150, blu_score);

	/* draw red banner */
	drawRedBanner(state, cr, state.padding + banner_width, state.padding, banner_width, 150, red_score);
}

#define LOGS_ROW_HEIGHT 64
#define LOGS_TEAM_LENGTH 146
#define LOGS_NAME_WIDTH 430

/* returns x offset for next draw off of */
static u16 drawPlayers_team(cairo_t *cr, u16 x, u16 y, cJSON *log, tf_player player, PangoFontDescription *fontd, PangoLayout *layout)
{
	/* create team-colored block */
	if(player.team == TF_BLUE)
		cairo_set_source_rgb(cr, CAT_EXTERN_BLUE);
	else
		cairo_set_source_rgb(cr, CAT_EXTERN_RED);
	cairo_rectangle(cr, x, y, LOGS_TEAM_LENGTH, LOGS_ROW_HEIGHT);
	cairo_fill(cr);

	/* faint shadows around east and south sides of block */
	/* minus 1's are to adjust for the line width */
	cairo_set_source_rgba(cr, 0, 0, 0, 0.05);
	cairo_move_to(cr, x, y + LOGS_ROW_HEIGHT - 1);
	cairo_line_to(cr, x + LOGS_TEAM_LENGTH - 1, y + LOGS_ROW_HEIGHT - 1);
	cairo_line_to(cr, x + LOGS_TEAM_LENGTH - 1, y);
	cairo_set_line_width(cr, 2);
	cairo_stroke(cr);


	u16 oldweight = pango_font_description_get_weight(fontd);
	u16 oldsize = pango_font_description_get_size(fontd);

	pango_font_description_set_weight(fontd, PANGO_WEIGHT_BOLD);
	pango_font_description_set_absolute_size(fontd, 24 * PANGO_SCALE);
	pango_layout_set_font_description(layout, fontd);
	

	if(player.team == TF_BLUE)
		pango_layout_set_text(layout, "BLU", -1);
	else
		pango_layout_set_text(layout, "RED", -1);

	/* center text */
	i32 cenx, ceny;
	pango_layout_get_pixel_size(layout, &cenx, &ceny);
	cenx = (x + (146 >> 1)) - (cenx >> 1);
	ceny = (y + (LOGS_ROW_HEIGHT >> 1)) - (ceny >> 1);

	cairo_set_source_rgb(cr, CAT_TEXT);
	cairo_move_to(cr, cenx, ceny);
	pango_cairo_show_layout(cr, layout);



	pango_font_description_set_weight(fontd, oldweight);
	pango_font_description_set_absolute_size(fontd, oldsize);
	pango_layout_set_font_description(layout, fontd);

	return LOGS_TEAM_LENGTH;
}

static u16 drawPlayers_name(cairo_t *cr, u16 x, u16 y, cJSON *log, tf_player player, PangoFontDescription *fontd, PangoLayout *layout)
{
	cJSON *namelist = cJSON_GetObjectItemCaseSensitive(log, "names");
	cJSON *name = cJSON_GetObjectItemCaseSensitive(namelist, player.sid3);

	/* get text height in pixels */
	i32 w1, h1;
	pango_layout_get_pixel_size(layout, &w1, &h1);

	/* show text */
	cairo_move_to(cr, x, (LOGS_ROW_HEIGHT >> 1) + y - (h1 >> 1));
	pango_layout_set_text(layout, name->valuestring, -1);
	cairo_set_source_rgb(cr, CAT_TEXT);
	pango_cairo_show_layout(cr, layout);

	return w1;
}

static u16 drawPlayers_split(cairo_t *cr, u16 x, u16 y)
{
	cairo_set_source_rgba(cr, CAT_OVERLAY0, 0.2);
	cairo_rectangle(cr, x, y, 4, LOGS_ROW_HEIGHT);
	cairo_fill(cr);

	return 4;
}

static void drawPlayers_row(gfx_state state, cairo_t *cr, u16 x, u16 y, bool color)
{
	if(color)
		cairo_set_source_rgb(cr, CAT_CRUST);
	else
		cairo_set_source_rgb(cr, CAT_MANTLE);
	cairo_rectangle(cr, x, y, state.width - (2*state.padding), LOGS_ROW_HEIGHT);
	cairo_fill(cr);
}

static void drawPlayers_stats(cairo_t *cr, u16 x, u16 y, tf_player player, PangoFontDescription *fontd, PangoLayout *layout)
{
	
}

static void drawPlayers_classes(cairo_t *cr, u16 x, u16 y, tf_player player)
{
	/* printf("%s ", player.sid3); */
	u8 offset = 0;
	for(u8 i = 0; i < 3 && player.class_stats[i].class != 0; i++)
	{
		cairo_surface_t *icon;

		switch(player.class_stats[i].class)
		{
			case TF_SCOUT:		icon = cairo_image_surface_create_from_png("class-icons/scout.png"); break;
			case TF_SOLDIER:	icon = cairo_image_surface_create_from_png("class-icons/soldier.png"); break;
			case TF_PYRO:		icon = cairo_image_surface_create_from_png("class-icons/pyro.png"); break;
			case TF_DEMOMAN:	icon = cairo_image_surface_create_from_png("class-icons/demoman.png"); break;
			case TF_HEAVY:		icon = cairo_image_surface_create_from_png("class-icons/heavy.png"); break;
			case TF_ENGINEER:	icon = cairo_image_surface_create_from_png("class-icons/engineer.png"); break;
			case TF_MEDIC:		icon = cairo_image_surface_create_from_png("class-icons/medic.png"); break;
			case TF_SNIPER:		icon = cairo_image_surface_create_from_png("class-icons/sniper.png"); break;
			case TF_SPY:		icon = cairo_image_surface_create_from_png("class-icons/spy.png"); break;
		}

		cairo_set_source_surface(cr, icon, x + offset, ((LOGS_ROW_HEIGHT >> 1) + y) - 20);
		cairo_paint(cr);

		offset += 40;
	}
}

static void drawPlayers_labels(gfx_state state, cairo_t *cr, u16 y, PangoFontDescription *fontd, PangoLayout *layout)
{
	u16 oldsize = pango_font_description_get_size(fontd);
	u16 oldweight = pango_font_description_get_weight(fontd);

	pango_font_description_set_absolute_size(fontd, 23 * PANGO_SCALE);
	pango_font_description_set_weight(fontd, PANGO_WEIGHT_MEDIUM);
	pango_layout_set_font_description(layout, fontd);
	
	pango_layout_set_text(layout, "Team", -1);

	i32 w, h;
	pango_layout_get_pixel_size(layout, &w, &h);

	/* center on Y axis */
	u32 ceny = ((LOGS_ROW_HEIGHT >> 1) + y) - (h >> 1);


	cairo_move_to(cr, state.padding + ((LOGS_TEAM_LENGTH >> 1) - (w >> 1)), ceny);
	printf("%d %d\n", w, h);


	cairo_set_source_rgb(cr, CAT_TEXT);
	pango_cairo_show_layout(cr, layout);

	drawPlayers_split(cr, state.padding + LOGS_TEAM_LENGTH, y);

	pango_layout_set_text(layout, "Name", -1);
	cairo_move_to(cr, state.padding + LOGS_TEAM_LENGTH + 4 + 8, ceny);
	cairo_set_source_rgb(cr, CAT_TEXT);
	pango_cairo_show_layout(cr, layout);

	drawPlayers_split(cr, state.padding + LOGS_NAME_WIDTH - 8, y);


	/* restore font */
	pango_font_description_set_absolute_size(fontd, oldsize);
	pango_font_description_set_weight(fontd, oldweight);
	pango_layout_set_font_description(layout, fontd);
}

void drawPlayers(gfx_state state, cairo_t *cr, cJSON *log)
{
	cJSON *playerlist = cJSON_GetObjectItemCaseSensitive(log, "players");

	PangoFontDescription *font_description;

	font_description = pango_font_description_new();
	pango_font_description_set_family(font_description, "Arial");
	pango_font_description_set_weight(font_description, PANGO_WEIGHT_NORMAL);
	pango_font_description_set_absolute_size(font_description, 23 * PANGO_SCALE);

	PangoLayout *layout = pango_cairo_create_layout(cr);
	pango_layout_set_font_description(layout, font_description);


	/* sort playerlist so teams are grouped together */
	sortplayers(&playerlist);


	u16 y = 297;
	bool color = 0;
	drawPlayers_labels(state, cr, y - LOGS_ROW_HEIGHT, font_description, layout);
	for(cJSON *p = playerlist->child; p != NULL; p = p->next)
	{
		u16 x = state.padding;
		tf_player player = parse_player(p);

		drawPlayers_row(state, cr, x, y, color);
		x += drawPlayers_team(cr, x, y, log, player, font_description, layout);
		x += drawPlayers_split(cr, x, y);
		x += drawPlayers_name(cr, x + 8, y, log, player, font_description, layout);

		/* names column hard limit */
		x = LOGS_NAME_WIDTH + 16;
		x += drawPlayers_split(cr, x, y);
		drawPlayers_classes(cr, x + 8, y, player);
		x = 430 + 16 + 8 + 8 + 8 + (3 * 40);
		drawPlayers_split(cr, x, y);
		drawPlayers_stats(cr, x, y, player, font_description, layout);


		color = !color;
		y += LOGS_ROW_HEIGHT;
	}


	g_object_unref(layout);
	pango_font_description_free(font_description);
}

void drawBoard(cJSON *log)
{
	/* u16 width = 1490; */
	u16 width = 1600;
	/* each player row is LOGS_ROW_HEIGHT tall; 24px padding on top and bottom;
	team score banner is 150px tall
	space between banner and score is 48px
	label row is 76 tall */
	u16 height = (getPlayerCount(cJSON_GetObjectItemCaseSensitive(log, "players")) * LOGS_ROW_HEIGHT) + 48 + 150 + 75 + 48;
	tf_game g = parse_game(log);
	gfx_state state;
	state.width = width;
	state.height = height;
	state.padding = 24;

	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cairo_t *cr = cairo_create(surface);

	/* draw background */
	cairo_set_source_rgb(cr, CAT_BASE);
	cairo_paint(cr);

	drawBanner(state, cr, g.blu_score, g.red_score);
	drawPlayers(state, cr, log);

	cairo_destroy(cr);
	cairo_surface_write_to_png(surface, "out.png");
	cairo_surface_destroy(surface);
}
