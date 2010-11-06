#ifndef CAIRO_DRAW_H
#define CAIRO_DRAW_H
/*************************************************************************************************
**on_expose_event_fadeout
**���뵭��Ч��
**
**************************************************************************************************/
gboolean on_expose_event_Fadeout(GtkWidget * widget, GdkEventExpose * event, gpointer data);
/*************************************************************************************************
**on_expose_event_Vertical
**��Ҷ��ģʽ
**
**************************************************************************************************/
gboolean on_expose_event_Vertical(GtkWidget *widget, GdkEventExpose *event, gpointer data);

/*************************************************************************************************
**on_expose_event_Spectrum
**����ģʽ
**
**************************************************************************************************/
gboolean on_expose_event_Spectrum(GtkWidget *widget, GdkEventExpose *event, gpointer data);

/*************************************************************************************************
**on_expose_event_Spectrum
**����ģʽ
**
**************************************************************************************************/
gboolean on_expose_event_Start(GtkWidget *widget, GdkEventExpose *event, gpointer data);

/*************************************************************************************************
**on_expose_event_rollText
**����ģʽ
**
**************************************************************************************************/
gboolean on_expose_event_rollText(GtkWidget *widget, GdkEventExpose *event, gpointer data);

typedef struct Expose_Fun
{
	guint interval;			//for g_timeout_add(guint interval, ...)
	gboolean (*expose_event_fun)(GtkWidget *widget, GdkEventExpose *event, gpointer data);
}Expose_Fun;

#endif
