#ifndef FNADVERPLAYER_DEF_H
#define FNADVERPLAYER_DEF_H

#define MAX_ADVER_AREAS 5
#define MAX_WIDGET_NAME_LEN 64

typedef struct AdverCairoPlayer
{
	gboolean timer;
	gint timer_id;
	gulong signal_handler;
	cairo_surface_t *image;
}AdverCairoPlayer;

typedef struct WidgetSize
{
	int width;
	int height;
}WidgetSize;

typedef struct WidgetPosition
{
	int x_position;
	int y_position;
}WidgetPosition;

typedef struct AreaDefInfo
{
	WidgetSize def_size;
	WidgetPosition def_position;
	gchar widget_name[MAX_WIDGET_NAME_LEN];
}AreaDefInfo;

typedef struct AdverDrawArea
{
	WidgetSize cur_size;
	WidgetPosition cur_position;
	AreaDefInfo area_def_info;
	GtkWidget *ad_darea;
	AdverCairoPlayer cariro_player;
}AdverDrawArea;

static const AreaDefInfo area_def_info[MAX_ADVER_AREAS] =
{
	{
		{200, 108},
		{0, 0},
		"image1"
	},
	{
		{200, 216},
		{0, 108},
		"image2"
	},
	{
		{200, 126},
		{0, 324},
		"image3"
	},
	{
		{600, 450},
		{200, 0},
		"image4"
	},
	{
		{800, 30},
		{0, 450},
		"image5"
	}
};
#endif
