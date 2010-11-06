#ifndef CAIRO_DRAW_H
#define CAIRO_DRAW_H
/*************************************************************************************************
**on_expose_event_fadeout
**淡入淡出效果
**
**************************************************************************************************/
gboolean on_expose_event_Fadeout(GtkWidget * widget, GdkEventExpose * event, gpointer data);
/*************************************************************************************************
**on_expose_event_Vertical
**百叶窗模式
**
**************************************************************************************************/
gboolean on_expose_event_Vertical(GtkWidget *widget, GdkEventExpose *event, gpointer data);

/*************************************************************************************************
**on_expose_event_Spectrum
**垂帘模式
**
**************************************************************************************************/
gboolean on_expose_event_Spectrum(GtkWidget *widget, GdkEventExpose *event, gpointer data);

/*************************************************************************************************
**on_expose_event_Spectrum
**星星模式
**
**************************************************************************************************/
gboolean on_expose_event_Start(GtkWidget *widget, GdkEventExpose *event, gpointer data);

/*************************************************************************************************
**on_expose_event_rollText
**滚条模式
**
**************************************************************************************************/
gboolean on_expose_event_rollText(GtkWidget *widget, GdkEventExpose *event, gpointer data);

typedef struct Expose_Fun
{
	guint interval;			//for g_timeout_add(guint interval, ...)
	gboolean (*expose_event_fun)(GtkWidget *widget, GdkEventExpose *event, gpointer data);
}Expose_Fun;

#endif
