/* Compile me with: 
*   gcc -o tut tut.c $(pkg-config --cflags --libs gtk+-2.0 gmodule-2.0) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h> 
#include "fnAdverPlayer.h"

static GtkWidget *mainfixed;
static GtkWidget *datelabel, *timelabel, *realtimelabel;

static ADVER_IMAGE_INFO ad_images[MAX_ADVER_AREAS];
 
int init_adver_image_info(GtkBuilder *builder);

int read_desktop_widgets(GtkBuilder *builder);
int init_desktop_widgets();


GtkWidget  *mainwindow;

#if 0
int main( int argc, char **argv ) 
{ 
	GtkBuilder *builder; 

	GError     *error = NULL; 
	
	/* Init GTK+ */
	gtk_init( &argc, &argv ); 
	 
	/* Create new GtkBuilder object */
	builder = gtk_builder_new(); 
	/* Load UI from file. If error occurs, report it and quit application. 
	* Replace "tut.glade" with your saved project. */
	if( ! gtk_builder_add_from_file( builder, "fnfixedwindow.glade", &error ) ) 
	{ //fnfixedwindow.glade	//fnstanderwindow
		g_warning( "%s", error->message ); 
		g_free( error ); 
		return( 1 ); 
	} 
	 
	/* Get main window pointer from UI */
	mainwindow = GTK_WIDGET( gtk_builder_get_object( builder, "mainwindow" ) ); 
	
	read_desktop_widgets(builder);
	init_desktop_widgets();

	/* Connect signals */
	gtk_builder_connect_signals( builder, NULL ); 
	 
	/* Destroy builder, since we don't need it anymore */
	g_object_unref( G_OBJECT( builder ) ); 
	
	
	gtk_widget_set_app_paintable(mainwindow, TRUE);
	/* Show window. All other widgets are automatically shown by GtkBuilder */
	gtk_widget_show( mainwindow ); 
	 
	/* Start main loop */
	gtk_main(); 
	 
	return( 0 ); 
}

int init_adver_image_info(GtkBuilder *builder)
{
	if(!builder)
	{
		g_warning("gtkbuilder null");
		return -1;
	}
	
	g_print("start %s\r\n", __FUNCTION__);

	int i = 0;
	memset(&ad_images, 0, sizeof(ad_images));

	for(i = 0; i < MAX_ADVER_AREAS; i++)
	{
		memcpy(&ad_images[i].area_def_info, &area_def_info[i], sizeof(AREA_DEF_INOF));
		ad_images[i].ad_image = GTK_IMAGE( gtk_builder_get_object(builder, ad_images[i].area_def_info.widget_name));

		if(!ad_images[i].ad_image)
		{
			g_warning("gtkbuilder get [%s] null", ad_images[i].area_def_info.widget_name);
		}
		else
			g_message("gtkbuilder get [%s : %08x]",
					ad_images[i].area_def_info.widget_name,
					ad_images[i].ad_image);
	}

	return 0;
}


int read_desktop_widgets(GtkBuilder *builder)
{
	if(!builder)
	{
		g_warning("gtkbuilder null");
		return -1;
	}

	init_adver_image_info(builder);

	mainfixed = GTK_WIDGET( gtk_builder_get_object( builder, "mainfixed"));
	if(!mainfixed)
	{
		g_warning("gtkbuilder get main fixed null");
	}

	datelabel = GTK_WIDGET( gtk_builder_get_object( builder, "datelabel")); 
	if(!datelabel)
	{
		g_warning("gtkbuilder get date label null");
	}

	timelabel = GTK_WIDGET( gtk_builder_get_object( builder, "timelabel"));
	if(!timelabel)
	{
		g_warning("gtkbuilder get time label null");
	}
	
	realtimelabel = GTK_WIDGET( gtk_builder_get_object( builder, "realtimelabel"));
	if(!realtimelabel)
	{
		g_warning("gtkbuilder get realtimelabel null");
	}
	return 0;
}

gboolean run_fish (gpointer data);
gboolean RepaintClock (gpointer data);
gboolean reflash_adver (gpointer data);
gboolean run_realtime_message(gpointer data);
static gboolean on_expose_event_Start(GtkWidget *widget, GdkEventExpose *event, gpointer data);
static gboolean on_expose_event_Spectrum(GtkWidget *widget, GdkEventExpose *event, gpointer data);
static gboolean on_expose_event_Vertical(GtkWidget *widget, GdkEventExpose *event, gpointer data);
static gboolean on_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer data);
static gboolean on_expose_event_fadeout(GtkWidget * widget, GdkEventExpose * event, gpointer data);

int init_desktop_widgets()
{
	//date label
	if(!datelabel)
	{
		g_warning("datelabe null");
	}
	else
	{
		gchar text[64];
		gchar markup[128];
		//GdkColor color;
		/*
		GTK_JUSTIFY_LEFT
		GTK_JUSTIFY_RIGHT
		GTK_JUSTIFY_CENTER
		GTK_JUSTIFY_FILL
		*/
		gtk_label_set_line_wrap (GTK_LABEL(datelabel), TRUE);
		gtk_label_set_justify(GTK_LABEL(datelabel), GTK_JUSTIFY_CENTER);

		sprintf(text, "%s", gtk_label_get_text(GTK_LABEL(datelabel)));

		sprintf(markup, "<span foreground='red' font_desc='22'>%s</span>", text);
		//标签，不可使用set_text
		gtk_label_set_markup(GTK_LABEL(datelabel), markup);
	}

	//time label
	if(!timelabel)
	{
		g_warning("timelabel null");
	}
	else
	{
		gchar text[64];
		gchar markup[128];
		//GdkColor color;
		/*
		GTK_JUSTIFY_LEFT
		GTK_JUSTIFY_RIGHT
		GTK_JUSTIFY_CENTER
		GTK_JUSTIFY_FILL
		*/
		gtk_label_set_line_wrap (GTK_LABEL(timelabel), TRUE);
		gtk_label_set_justify(GTK_LABEL(timelabel), GTK_JUSTIFY_CENTER);

		sprintf(text, "%s", gtk_label_get_text(GTK_LABEL(timelabel)));

		sprintf(markup, "<span foreground='yellow' font_desc='16'>%s</span>", text);
		//标签，不可使用set_text
		gtk_label_set_markup(GTK_LABEL(timelabel), markup);

		gtk_timeout_add(3000, run_fish, NULL);
		gtk_timeout_add(1000, RepaintClock, timelabel);
		gtk_timeout_add(5000, reflash_adver, NULL);
		gtk_timeout_add(30, run_realtime_message, NULL);
	//	gtk_widget_set_app_paintable(ad_images[4].ad_image, TRUE);
		//ad_images[4].ad_image
		g_signal_connect(G_OBJECT(mainwindow), "expose-event", G_CALLBACK(on_expose_event_fadeout), NULL);//on_expose_event_Vertical on_expose_event_Spectrum

	}

	return 0;
}

gboolean run_fish (gpointer data)
{
	static int x = 40;
	static int y = 170;
	
	srand(time(NULL));//产生随机数种子
	x = rand() % 710 + 1;//产生一个1~750以内的随机数.
	y = rand() % 450 + 1;
//	x = (x%750);
//	y = (y%450);

	if(mainfixed && timelabel)
	{
			gtk_fixed_move (GTK_FIXED (mainfixed), timelabel, x, y); 
	}
	return TRUE;
}

#include <cairo.h>

gboolean timer = FALSE;
cairo_surface_t *image;

static gboolean time_handler_start(GtkWidget *widget)
{
	if (widget->window == NULL)
	{
		printf("%s widget->window  null\r\n", __FUNCTION__, gtk_widget_get_name(widget));
		return FALSE;
	}
	if (!timer)
		return TRUE;
	gtk_widget_queue_draw(widget);
	return TRUE;
}      

int points[11][2] =
{
	{ 0, 85 },
	{ 75, 75 },
	{ 100, 10 },
	{ 125, 75 },
	{ 200, 85 },
	{ 150, 125 },
	{ 160, 190 },
	{ 100, 150 },
	{ 40, 190 },
	{ 50, 125 },
	{ 0, 85 }
};


static gboolean on_expose_event (GtkWidget * widget, GdkEventExpose * event, gpointer data)
{
	cairo_t *cr;
	cairo_pattern_t *pat1;
	cairo_pattern_t *pat2;
	cairo_pattern_t *pat3;

	cr = gdk_cairo_create (widget->window);

	pat1 = cairo_pattern_create_linear (0.0, 0.0, 350.0, 350.0);

	gdouble j;
	gint count = 1;
	for (j = 0.1; j < 1; j += 0.1)
	{
		if ((count % 2))
		{
			cairo_pattern_add_color_stop_rgb (pat1, j, 0, 0, 0);
		}
		else
		{
			cairo_pattern_add_color_stop_rgb (pat1, j, 1, 0, 0);
		}
		count++;
	}

	cairo_rectangle (cr, 20, 20, 300, 100);
	cairo_set_source (cr, pat1);
	cairo_fill (cr);


	pat2 = cairo_pattern_create_linear (0.0, 0.0, 350.0, 0.0);

	gdouble i;
	count = 1;
	for (i = 0.05; i < 0.95; i += 0.025)
	{
		if ((count % 2))
		{
			cairo_pattern_add_color_stop_rgb (pat2, i, 0, 0, 0);
		}
		else
		{
			cairo_pattern_add_color_stop_rgb (pat2, i, 0, 0, 1);
		}
		count++;
	}

	cairo_rectangle (cr, 20, 140, 300, 100);
	cairo_set_source (cr, pat2);
	cairo_fill (cr);


	pat3 = cairo_pattern_create_linear (20.0, 260.0, 20.0, 360.0);

	cairo_pattern_add_color_stop_rgb (pat3, 0.1, 0, 0, 0);
	cairo_pattern_add_color_stop_rgb (pat3, 0.5, 1, 1, 0);
	cairo_pattern_add_color_stop_rgb (pat3, 0.9, 0, 0, 0);

	cairo_rectangle (cr, 20, 260, 300, 100);
	cairo_set_source (cr, pat3);
	cairo_fill (cr);

	cairo_pattern_destroy (pat1);
	cairo_pattern_destroy (pat2);
	cairo_pattern_destroy (pat3);

	cairo_destroy (cr);

	return FALSE;
}

static gboolean on_expose_event_fadeout(GtkWidget * widget, GdkEventExpose * event, gpointer data)
{
	cairo_t *cr;

	static double alpha = 0;
	double const delta = 0.01;
	if(!image)
		return FALSE;
	cr = gdk_cairo_create (widget->window);//gdk_cairo_create
	cairo_set_source_surface (cr, image, 0, 0);

	if(timer)
	{
		cairo_paint_with_alpha (cr, alpha);

		alpha += delta;

		if (alpha >= 1)
		{
			timer = FALSE;
			alpha = 0;
		}

	}
	else
	{
		printf("time false paint : %d\r\n", alpha);
		cairo_paint(cr);
	}

	cairo_destroy (cr);

	return FALSE;
}

static gboolean on_expose_event_Vertical(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
  cairo_t *cr;
  cairo_t *ic;

  cairo_surface_t *surface;

  static gdouble angle = 0;
  static gint w = 0;
  static gint h = 0;

  static gint image_width = 0;
  static gint image_height = 0;

  static gint count = 0;


  gint width, height;
	if(!image)
	{
		// || timer == FALSE
		return FALSE;
	}

	
	width = 600;
	height = 450;
	cr = gdk_cairo_create(widget->window);
	if(timer == TRUE)
	{
		gtk_widget_get_size_request(widget, &width, &height);

		//  gtk_window_get_size(GTK_WINDOW(widget), &width, &height); 

		surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, image_width, image_height);  
	
		image_width = cairo_image_surface_get_width(image);
		image_height = cairo_image_surface_get_height(image);
		w = image_width;  

		ic = cairo_create(surface);

		gint i, j;

		for (i = 0; i <= image_height; i+=7) {
		  printf("move : %d\r\n", count);
		  for (j=0 ; j < count; j++) {
			  cairo_move_to(ic, 0, i+j);
			  cairo_line_to(ic, w, i+j);
		  }
		}

		count++;
		if ( count == 8){
		  count = 0;
		  timer = FALSE;
		}
		cairo_stroke(ic);

		cairo_set_source_surface(cr, image, 0, 0);
		cairo_mask_surface(cr, surface, 0, 0);

		cairo_surface_destroy(surface);

		cairo_destroy(cr);
		cairo_destroy(ic);
	}
	else
	{
		printf("time false paint : %d\r\n", count);
		cairo_set_source_surface(cr, image, 0, 0);
		cairo_paint(cr);
		cairo_destroy(cr); 	
	}
  return FALSE;
}

static gboolean on_expose_event_Spectrum(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	cairo_t *cr;
	cairo_t *ic;
	cairo_surface_t *surface;
	static gdouble angle = 0;
	static gint w = 0;
	static gint h = 0;
	static gint image_width = 0;
	static gint image_height = 0;
	static gint count = 0;

	if(!image || !timer)
		return FALSE;

	cr = gdk_cairo_create(widget->window);
	//printf("%s play on : %s\r\n", __FUNCTION__, gtk_widget_get_name(widget));

	gint width, height;

//	width = 600;
//	height = 450;
	//gtk_window_get_size(GTK_WINDOW(widget), &width, &height);
	gtk_widget_get_size_request(widget, &width, &height);
	
	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, image_width, image_height);
	image_width = cairo_image_surface_get_width(image);
	image_height = cairo_image_surface_get_height(image);
	w = image_width;
	ic = cairo_create(surface);
	gint i, j;
	for (i = 0; i <= image_height; i+=7)
	{
		for (j=0 ; j < count; j++)
		{
			cairo_move_to(ic, 0, i+j);
			cairo_line_to(ic, w, i+j);
		}
	}
	count++;
	if ( count == 8)
	{
		timer = FALSE;
		printf("%s play on Over: %s\r\n", __FUNCTION__, gtk_widget_get_name(widget));
	}
	cairo_stroke(ic);
	cairo_set_source_surface(cr, image, 0, 0);
	cairo_mask_surface(cr, surface, 0, 0);
	cairo_surface_destroy(surface);
	cairo_destroy(cr);
	cairo_destroy(ic);
	return FALSE;
} 

static gboolean on_expose_event_Start(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	cairo_t *cr;
	static gdouble angle = 0;
	static gdouble scale = 1;
	static gdouble delta = 0.01;
	gint width, height;
	//gtk_window_get_size(widget, &width, &height);
	//gtk_widget_get_size_request(widget, &width, &height);
	if(!image)
		return FALSE;
	width = 600;
	height = 450;
	//printf("%s play on : %s\r\n", __FUNCTION__, gtk_widget_get_name(widget));

	cr = gdk_cairo_create(widget->window);
	cairo_set_source_rgb(cr, 0, 0.44, 0.7);
	cairo_set_line_width(cr, 1);
	cairo_translate(cr, width / 2, height / 2 );
	cairo_rotate(cr, angle);
	cairo_scale(cr, scale, scale);
	gint i;
	for ( i = 0; i < 10; i++ )
	{
		cairo_line_to(cr, points[i][0], points[i][1]);
	}
	cairo_close_path(cr);
	cairo_fill(cr);
	cairo_stroke(cr);
	if ( scale < 0.01 )
	{
		delta = -delta;
	}
	else if (scale > 0.99)
	{
		delta = -delta;
	}
	scale += delta;
	angle += 0.01;
	cairo_destroy(cr);
	return FALSE;
}

gboolean reflash_adver(gpointer data)
{
    time_t now;
	gchar buf[24];
	gchar markup[128];
    struct tm *now_tm;

    GtkWidget*	drawing_entry = (GtkWidget *) data;

	time (&now);

	static gint runtime = 0;
	int i = 0;
	char name[64];
	srand(time(NULL));//产生随机数种子
	//g_signal_disconnect
	static gulong id = 0;
	static int timerid = 0;

	if(runtime++ % 3 == 0)
	{
		static int index = 0;
		index++;

		if(!timerid)
			gtk_timeout_remove(timerid);

		i = rand() % MAX_ADVER_AREAS;
		cairo_status_t status;
		if(image != NULL)
		{
			cairo_surface_destroy(image);
		}

		sprintf(name, "./images/image_%d_%d.jpg", 4, index%3);

		image = cairo_image_surface_create_from_jpeg(name, &status);
	
		printf("cairo_image_surface : %s\r\n", name);

		timerid = g_timeout_add(50, (GSourceFunc)time_handler_start, (gpointer)mainwindow); //ad_images[4].ad_image
		
		timer = TRUE;
	}

    return (TRUE);
}

gboolean RepaintClock (gpointer data)
{
    time_t now;
	gchar buf[24];
	gchar markup[128];
    struct tm *now_tm;

    GtkWidget*	drawing_entry = (GtkWidget *) data;

	time (&now);

    /* --- Convert time --- */
    now_tm = localtime (&now);
	gint year	= now_tm->tm_year;
	gint month	= now_tm->tm_mon;
	gint day	= now_tm->tm_mday;
	gint second = now_tm->tm_sec;
	gint minute = now_tm->tm_min;
	gint hour = now_tm->tm_hour;
/*
	if(second%2)
		sprintf(buf,"鏃堕棿:%04d-%02d-%02d %02d : %02d :%02d",
			year+1900,
			month+1,
			day,
			hour,
			minute,
			second);
	else
		sprintf(buf,"鏃堕棿:%04d-%02d-%02d %02d : %02d  %02d",
			year+1900,
			month+1,
			day,
			hour,
			minute,
			second);
*/
	if(second%2)
		sprintf(buf,"泛网提醒您:%02d:%02d", hour, minute);
	else
		sprintf(buf,"泛网提醒您:%02d %02d", hour, minute);

	sprintf(markup, "<span foreground='yellow' font_desc='16'>%s</span>", buf);
	//标签，不可使用set_text
	gtk_label_set_markup(GTK_LABEL(drawing_entry), markup);


/*
	static gint runtime = 0;
	int i = 0;
	char name[12];
	srand(time(NULL));//产生随机数种子

	if(runtime++ % 3 == 0)
	{
		static int index = 0;
		index++;
		if(runtime <= 1)
			for(i = 0; i < MAX_ADVER_AREAS; i++)
			{
				//
				sprintf(name, "./images/image_%d_%d.jpg", i+1, index%3);
				g_print("first chang pic : %s\r\n", name);
				if(ad_images[i].ad_image)
					gtk_image_set_from_file(ad_images[i].ad_image, name);
			}
		else
		{
			i = rand() % MAX_ADVER_AREAS;
			sprintf(name, "./images/image_%d_%d.jpg", i+1, index%3);
			g_print("next chang pic : %s\r\n", name);
			if(ad_images[i].ad_image)
				gtk_image_set_from_file(ad_images[i].ad_image, name);
		}
	}
*/
    return (TRUE);
}

gboolean run_realtime_message(gpointer data)
{
//
	gchar buf[512];
	gchar markup[1024];
	const int max_eche = 10;			//10ms
	const int max_chang = 2000;	//3s
	static int runtime = 0;

	const int y_start = 450;
	const int y_end = 390;
	int y_diff = 10;

	if(realtimelabel != NULL)
	{
		int k = runtime++ % (max_chang/max_eche);
		if( k > 0 && k < (y_start-y_end))	//翻滚
		{
			gtk_widget_show(realtimelabel);
			sprintf(buf,"%s",
						"  人民网9月20日电 据香港文汇报报道，菲律宾外交部昨发表声明表示，将尽快把上月发生马尼拉挟持人质惨剧的调查报告，送交中国外交人员(XXX报道)");
			sprintf(markup, "<span foreground='red' font_desc='18.4'>%s</span>", buf);
			//标签，不可使用set_text
			gtk_label_set_markup(GTK_LABEL(realtimelabel), markup);
			if(mainfixed)
			{
					gtk_fixed_move (GTK_FIXED (mainfixed), realtimelabel, 2, y_start-k);
					//g_message("move realtime message :%d\r\n", y_start-k);
			}
		}
		else
		{
				//gtk_fixed_move (GTK_FIXED (mainfixed), realtimelabel, 0, 450);
				//g_message("sleep realtime message :%d\r\n", k);
				gtk_widget_hide(realtimelabel);
		}
	}
	return (TRUE);
}

#else

#include <cairo.h>

//gboolean timer = FALSE;
cairo_surface_t *image_a, *image_b;

static gboolean on_expose_event_a (GtkWidget * widget, GdkEventExpose * event, gpointer data)
{
	cairo_t *cr;
	
	cr = gdk_cairo_create (widget->window);
	static gboolean timer = FALSE;
	static double alpha = 0;
	double const delta = 0.01;

//	cairo_set_source_surface(cr, image, 0, 0);
//	cairo_paint(cr);
//	cairo_destroy(cr); 	

	cairo_set_source_surface (cr, image_a, 0, 0);
//	cairo_paint(cr);
	cairo_paint_with_alpha (cr, alpha);
	
	alpha += delta;

	if (alpha >= 1)
	{	
		alpha = 0;
		timer = FALSE;
	}
	else
	{
		//printf("alpha : %f\r\n", alpha);
	}

	cairo_destroy (cr);

	return FALSE;
}

static gboolean on_expose_event_b (GtkWidget * widget, GdkEventExpose * event, gpointer data)
{
	cairo_t *cr;

	cr = gdk_cairo_create (widget->window);

	static gboolean timer = FALSE;
	static double alpha = 0;
	double const delta = 0.01;

//	cairo_set_source_surface(cr, image, 0, 0);
//	cairo_paint(cr);
//	cairo_destroy(cr); 	

	cairo_set_source_surface (cr, image_b, 0, 0);
//	cairo_paint(cr);
	cairo_paint_with_alpha (cr, alpha);

	if(timer == FALSE)
	{
		alpha += delta;
		if (alpha >= 1)
		{	
			//alpha = 0;
			timer = TRUE;
		}
	}
	else
	{
		alpha -= delta;
		if (alpha <= 0)
		{	
			//alpha = 1;
			timer = FALSE;
		}
	}

	cairo_destroy (cr);

	return FALSE;
}

static gboolean time_handler (GtkWidget * widget)
{
	if (widget->window == NULL)
		return FALSE;

	gtk_widget_queue_draw (widget);
	return TRUE;
}

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *darea_a, *darea_b;

	gint width, height;
	cairo_status_t status;

	char name[64];

	image_a = cairo_image_surface_create_from_png ("plaveckycastle.png");
//	width = cairo_image_surface_get_width (image);
//	height = cairo_image_surface_get_height (image);
//	}
//	else
//	{
		width = 600;
		height = 480;
		image_b = cairo_image_surface_create_from_jpeg("./images/image_4_1.jpg", &status);
//	}
	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	GtkWidget *fixed = gtk_fixed_new ();
	gtk_container_add(GTK_CONTAINER(window),fixed);

//////////////////////////////////////////////////////////////////////////////////////////
	darea_a = gtk_drawing_area_new ();
	gtk_drawing_area_size (GTK_DRAWING_AREA (darea_a), 200, 200);

	gtk_container_add (GTK_CONTAINER (fixed), darea_a);

	gtk_fixed_move (GTK_FIXED (fixed), darea_a, 0, 0); 

	g_signal_connect (darea_a, "expose-event", G_CALLBACK (on_expose_event_a), NULL);

//////////////////////////////////////////////////////////////////////////////////////////
	darea_b = gtk_drawing_area_new ();
	gtk_drawing_area_size (GTK_DRAWING_AREA (darea_b), 600, 480);

	gtk_container_add (GTK_CONTAINER (fixed), darea_b);

	gtk_fixed_move (GTK_FIXED (fixed), darea_b, 200, 0); 

	g_signal_connect (darea_b, "expose-event", G_CALLBACK (on_expose_event_b), NULL);

/////////////////////////////////////////////////////////////////////////////////////////	
//////////////////////////////////////////////////////////////////////////////////////////

	GtkWidget *label = gtk_label_new ("123456789012345678901234567890");
	gtk_container_add (GTK_CONTAINER (fixed), label);
	gtk_fixed_move (GTK_FIXED (fixed), label, 0, 240); 
	gtk_widget_show(label);
/////////////////////////////////////////////////////////
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size (GTK_WINDOW (window), width, height);

	gtk_window_set_title (GTK_WINDOW (window), "fade out");
	g_timeout_add (50, (GSourceFunc) time_handler, (gpointer) darea_a);
	g_timeout_add (10, (GSourceFunc) time_handler, (gpointer) darea_b);
	gtk_widget_show_all (window);

	gtk_main ();

	cairo_surface_destroy (image_a);
	cairo_surface_destroy (image_b);

	return 0;
}


#endif