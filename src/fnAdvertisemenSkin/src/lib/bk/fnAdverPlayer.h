#ifndef FNADVERPLAYER_DEF_H
#define FNADVERPLAYER_DEF_H

#define MAX_ADVER_AREAS 5
#define MAX_WIDGET_NAME_LEN 64

typedef struct WG_SIZE
{
	int width;
	int height;
}WG_SIZE;

typedef struct WG_POSITION
{
	int x_position;
	int y_position;
}WG_POSITION;

typedef struct AREA_DEF_INOF
{
	WG_SIZE def_size;
	WG_POSITION def_position;
	gchar widget_name[MAX_WIDGET_NAME_LEN];
}AREA_DEF_INOF;

typedef struct ADVER_IMAGE_INFO
{
	WG_SIZE cur_size;
	WG_POSITION cur_position;
	AREA_DEF_INOF area_def_info;
	GtkImage *ad_image;
}ADVER_IMAGE_INFO;

const AREA_DEF_INOF area_def_info[MAX_ADVER_AREAS] =
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
