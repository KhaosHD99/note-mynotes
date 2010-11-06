#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "fnAdvertisemenSkin.h"

#include "cairodraw.h"


static gboolean button_press_event_handle(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	switch(event->button)
	{
		case 1:
		    printf("Left press on : %s\r\n", gtk_widget_get_name(widget));
		    break;
		case 2:
		    printf("Middle press on : %s\r\n", gtk_widget_get_name(widget));
		    break;
		case 3:
		    printf("Right press on : %s\r\n", gtk_widget_get_name(widget));
		    break;
		default:
		    printf("Unknown press on : %s\r\n", gtk_widget_get_name(widget));
    }
}

static gboolean button_release_event_handle(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	switch(event->button)
	{
		case 1:
		    printf("Left release on : %s\r\n", gtk_widget_get_name(widget));
		    break;
		case 2:
		    printf("Middle release on : %s\r\n", gtk_widget_get_name(widget));
		    break;
		case 3:
		    printf("Right release on : %s\r\n", gtk_widget_get_name(widget));
		    break;
		default:
		    printf("Unknown release on : %s\r\n", gtk_widget_get_name(widget));
    }
}
