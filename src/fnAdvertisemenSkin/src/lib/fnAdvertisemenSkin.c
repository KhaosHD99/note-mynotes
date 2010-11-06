#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include "LogMsg.hpp"
#include "cairodraw.h"
#include "fnAdvertisemenSkin.h"

//仅提供窗口及播放初始化API
#define MAX_EXPOSE_FUN_NUM 5
#define MAX_PLAYER_AREA_NUM 5


typedef enum{
	FADEOUT = 0,
	VERTICAL,
	SPECTRUM,
	START,
	TEXTROLL
}Exposer;

static const Expose_Fun expose_funs[MAX_EXPOSE_FUN_NUM] = {

	{	
	10,		
	&on_expose_event_Fadeout
	},
	{	
	10,		
	&on_expose_event_Vertical,
	},
	{	
	120,		
	&on_expose_event_Spectrum,
	},
	{	
	10,		
	&on_expose_event_Start
	},
	{	
	100,		
	&on_expose_event_rollText
	},
};

static AdverDrawArea adverDrawArea[MAX_PLAYER_AREA_NUM];

int get_playarea_num()
{
	return MAX_PLAYER_AREA_NUM;
}
/******************************************************************
**
**创建播放区
**
******************************************************************/
static int creat_playarea(unsigned int index)
{
		if(index < 0 || index >= get_playarea_num())
		{
			showWarning("%s index error : %d\r\n", __FUNCTION__);
			return -1;	
		}
		GtkWidget *darea;
		gchar image_name[64];
		cairo_status_t status;
		assert(adverDrawArea[index].cur_position.x_position >= 0);
		assert(adverDrawArea[index].cur_position.x_position >= 0);
		assert(adverDrawArea[index].cur_size.width >= 0);
		assert(adverDrawArea[index].cur_size.height >= 0);
		
		if(adverDrawArea[index].ad_darea == NULL)
		{
			darea = gtk_drawing_area_new ();

			gtk_widget_set_name(darea, "adver_darea_1");
			
			adverDrawArea[index].ad_darea = darea;
			
			gtk_drawing_area_size (GTK_DRAWING_AREA (darea),
									adverDrawArea[index].cur_size.width,
									adverDrawArea[index].cur_size.height);
			//加入单击事件
			gtk_widget_add_events(darea, GDK_BUTTON_PRESS_MASK);
			gtk_widget_add_events(darea, GDK_BUTTON_RELEASE_MASK);
			
	//		g_signal_connect (darea, "button_press_event", G_CALLBACK (button_press_event_handle), (gpointer)&adverDrawArea[index]);
	//		g_signal_connect (darea, "button_release_event", G_CALLBACK (button_release_event_handle), (gpointer)&adverDrawArea[index]);
	//		adverDrawArea[index].cariro_player.image = cairo_image_surface_create_from_png ("plaveckycastle.png");
			//设定默认播放图片			
			sprintf(image_name, "./images/image_%d_0.jpg", index+1);
			adverDrawArea[index].cariro_player.image = cairo_image_surface_create_from_jpeg ((const char *)image_name, &status);
			//设定默认播放函数
			//adverDrawArea[index].cariro_player.signal_handler = g_signal_connect (darea, "expose-event", G_CALLBACK (on_expose_event_Fadeout), (gpointer)&adverDrawArea[index]);
			adverDrawArea[index].cariro_player.signal_handler = 
										g_signal_connect (darea, 
																			"expose-event",
																			G_CALLBACK (expose_funs[index%MAX_EXPOSE_FUN_NUM].expose_event_fun),
																			(gpointer)&adverDrawArea[index]);
		}
		else
		{
			showWarning("play area[%d] was been creat!\r\n");		
		}
		showWarning("%s over\r\n", __FUNCTION__);
		return 0;
}

/******************************************************************
**
**释放播放区
**
******************************************************************/
static int delete_playarea(unsigned int index)
{
	
	return 0;
}
/******************************************************************
**
**初始化并创建播放区域
**
******************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
int init_play_areas()
{
	int ret = 0;
	int index = 0;
	memset(&adverDrawArea, 0, sizeof(adverDrawArea));

	for(index = 0; index < get_playarea_num(); index++)
	{
		//从默认表内加载
		memcpy(&adverDrawArea[index].area_def_info, &area_def_info[index], sizeof(AreaDefInfo));

		adverDrawArea[index].cur_size.width = area_def_info[index].def_size.width;
		adverDrawArea[index].cur_size.height = area_def_info[index].def_size.height;
		adverDrawArea[index].cur_position.x_position = area_def_info[index].def_position.x_position;
		adverDrawArea[index].cur_position.y_position = area_def_info[index].def_position.y_position;
		
		ret = creat_playarea(index);
		
		if(ret != 0)
		{
				showWarning("creat play area failed!\r\n");
		}
	}	
	
	return 0;
}
#ifdef __cplusplus
extern "C"
}
#endif

static gboolean time_handler (GtkWidget * widget)
{
	if (widget->window == NULL)
	{
		printf("%s window null\r\n", gtk_widget_get_name(widget));
		return FALSE;
	}

	gtk_widget_queue_draw (widget);

	return TRUE;
}
/******************************************************************
**
**模拟广告驱动
**
******************************************************************/
gpointer signal_thread(gpointer arg) 
{	
	char name[64];
	GtkWidget *darea;
	cairo_status_t status;

	darea = adverDrawArea[5].ad_darea;

	sprintf(name, "./images/image_%d_%d.jpg", 1, 0);

	adverDrawArea[5].cariro_player.image = cairo_image_surface_create_from_jpeg((const char *)name, &status);

	adverDrawArea[5].cariro_player.timer = TRUE;

	adverDrawArea[5].cariro_player.timer_id = g_timeout_add(30, (GSourceFunc)time_handler, (gpointer)darea); //ad_images[4].ad_image

}

static gboolean simulation_adver(gpointer data)
{
	time_t now;
	gchar buf[24];
	gchar markup[128];
	struct tm *now_tm;

//	GtkWidget*	drawing_entry = (GtkWidget *) data;
	
	time (&now);

	static gint runtime = 0;
	static gint exposer = 0;
	int draw_index = 0;
	char name[64];
	srand(time(NULL));

	GtkWidget *darea;
	if(runtime++ % 3 == 0)
	{
		static int last_draw = -1;
		static int pic_num = 0;

		draw_index = pic_num % MAX_ADVER_AREAS;;//rand() % MAX_ADVER_AREAS;
		
		if(exposer%MAX_EXPOSE_FUN_NUM == 4)	//如果是刷滚条的话，只允许涮第五区
		{
				draw_index = MAX_ADVER_AREAS-1;
				g_warning("+++++++++play module [%d] in area [%d] spc\r\n", exposer%MAX_EXPOSE_FUN_NUM, draw_index);
		}
		
		if(last_draw == draw_index)
		{
			g_warning("play last area : %d\r\n", last_draw);
			if(adverDrawArea[draw_index].cariro_player.timer_id)
			{
				g_warning("last play area using: %d\r\n", last_draw);
				return TRUE;
			}
		}
		last_draw = draw_index;

		darea = adverDrawArea[draw_index].ad_darea;
		
		if(darea)
		{
			if(adverDrawArea[draw_index].cariro_player.timer_id != 0)
			{
				g_warning("reflash_adver : draw area [%d] timer live : %d \r\n",
					draw_index, adverDrawArea[draw_index].cariro_player.timer_id);
				gtk_timeout_remove(adverDrawArea[draw_index].cariro_player.timer_id);
				adverDrawArea[draw_index].cariro_player.timer_id = 0;
			}
			
			if(adverDrawArea[draw_index].cariro_player.signal_handler != 0)
			{
				g_warning("reflash_adver : draw area [%d] signal handler: %d \r\n",
					draw_index, adverDrawArea[draw_index].cariro_player.signal_handler);

				g_signal_handler_disconnect((gpointer)adverDrawArea[draw_index].ad_darea, 
											adverDrawArea[draw_index].cariro_player.signal_handler);

				adverDrawArea[draw_index].cariro_player.signal_handler = 0;
			
			}
			cairo_status_t status;

			if(adverDrawArea[draw_index].cariro_player.image != NULL)
			{
				cairo_surface_destroy(adverDrawArea[draw_index].cariro_player.image);
				adverDrawArea[draw_index].cariro_player.image = NULL;
			}

			sprintf(name, "./images/image_%d_%d.jpg", draw_index+1, pic_num%3);

			adverDrawArea[draw_index].cariro_player.image = cairo_image_surface_create_from_jpeg((const char *)name, &status);

			adverDrawArea[draw_index].cariro_player.signal_handler = g_signal_connect (darea,
																		"expose-event",
																		G_CALLBACK (expose_funs[exposer%MAX_EXPOSE_FUN_NUM].expose_event_fun),
																		(gpointer)&adverDrawArea[draw_index]);
			adverDrawArea[draw_index].cariro_player.timer = TRUE;

			adverDrawArea[draw_index].cariro_player.timer_id = g_timeout_add(expose_funs[exposer%MAX_EXPOSE_FUN_NUM].interval,
														(GSourceFunc)time_handler,
														(gpointer)darea); //ad_images[4].ad_image

			printf("cairo [%s, interval : %d] image_surface : %s, on timer : %d, on signed handler : %d, on exposer : %d\r\n", 
					adverDrawArea[draw_index].area_def_info.widget_name, 
					expose_funs[exposer%MAX_EXPOSE_FUN_NUM].interval,
					name,
					adverDrawArea[draw_index].cariro_player.timer_id,
					adverDrawArea[draw_index].cariro_player.signal_handler,
					exposer%MAX_EXPOSE_FUN_NUM);

		}
		else
			printf("cairo [%d] draw area null\r\n", draw_index);
		exposer++;
		pic_num++;
			
	}
    return (TRUE);
}

#ifdef __cplusplus
extern "C"
{
#endif
int tick_adver_simulation()
{
	return simulation_adver(NULL);	
}
#ifdef __cplusplus
}
#endif

/******************************************************************
**
**创建播放界面
**
******************************************************************/
struct st_argvs
{
	int argc;
	char **argv;	
};

#ifdef __cplusplus
extern "C"
{
#endif
int init_play_window(struct st_argvs *argvs)
{
	int ret = 0;

	Window xWindow;
	Display *display;
	GtkWidget *window;
	GtkWidget *darea;//darea_1, *darea_2, *darea_3, *darea_4;

	gint width, height;
	cairo_status_t status;

	char name[64];


	gtk_init (&argvs->argc, &argvs->argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "MainWindow");

	ret = init_play_areas();

	GtkWidget *fixed = gtk_fixed_new ();
	gtk_container_add(GTK_CONTAINER(window),fixed);
//area a
//////////////////////////////////////////////////////////////////////////////////////////
	int index = 0;
	for(index = 0; index < MAX_ADVER_AREAS; index++)
	{
		darea = adverDrawArea[index].ad_darea;
		if(darea)
		{printf("0.%d \n", index);
			gtk_container_add (GTK_CONTAINER (fixed), darea);

			printf("gtk_container_add : %s \r\n", gtk_widget_get_name(darea));

			gtk_fixed_move (GTK_FIXED (fixed),
							darea,
							adverDrawArea[index].cur_position.x_position,
								adverDrawArea[index].cur_position.y_position); 
			printf("%d \n", index);
			adverDrawArea[index].cariro_player.timer_id = g_timeout_add (30, (GSourceFunc) time_handler, (gpointer) darea);
		}
		else
			printf("adver draw area [%d] null\r\n", index);
	}
	
//////////////////////////////////////////////////////////////////////////////////////////

	GtkWidget *label = gtk_label_new ("123456789012345678901234567890");
	gtk_container_add (GTK_CONTAINER (fixed), label);
	gtk_fixed_move (GTK_FIXED (fixed), label, 0, 10); 
	gtk_widget_show(label);


	/////////////////////////////////////////////////////////
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size (GTK_WINDOW (window), 800, 480);

	
	gtk_timeout_add(1500, simulation_adver, NULL);

	gtk_widget_show_all (window);

//////////////////////////////////////////////////////////////////
	//?μ?°???μ?11 Display
    xWindow = GDK_WINDOW_XID(window->window);

	if ( (display=GDK_WINDOW_XDISPLAY(window->window)) == NULL )
	{
		printf("Cannot connect to X server \n");
		return NULL;
	}
	else
		printf("connect to Xserver on XWindow %d\r\n", xWindow);
////////////////////////////////////////////////////////////////
	
	//FLAG = `pkg-config --cflags --libs gtk+-2.0 gthread-2.0` -export-dynamic
	if(!g_thread_supported()) {
        g_thread_init(NULL);
    }	
    g_thread_create(signal_thread, NULL, FALSE, NULL);
	//*/
	gtk_main ();

	for(index = 0; index < MAX_ADVER_AREAS; index++)
	{
		if(adverDrawArea[index].cariro_player.image)
			cairo_surface_destroy (adverDrawArea[index].cariro_player.image);
	}
	return 0;

	
}
#ifdef __cplusplus
extern "C"
}
#endif

