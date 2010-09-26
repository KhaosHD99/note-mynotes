#include<libintl.h>
#include<locale.h>
#include<stdio.h>
#include<gtk/gtk.h>

#define _(String) gettext (String)
#define _t(String1,String2,n) ngettext (String1,String2,n)

//const gchar *list_item_data_key="list_item_data";

//static void  sigh_print_selection( GtkWidget *gtklist,
//                                   gpointer   func_data);

//static void  sigh_button_event( GtkWidget      *gtklist,
//                                GdkEventButton *event,
 //                               GtkWidget      *frame );
int main(int argc, char *argv[])
{
    int i;
    setlocale(LC_ALL,"");
  //  bindtextdomain("hello", "./locale");
    textdomain("hello");
    printf(_("Hello World"));
    printf("\n");
   
    /*GtkWidget *separator;
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *scrolled_window;
    GtkWidget *frame;
    GtkWidget *gtklist;
    GtkWidget *list_item;
    //GList *dlist;
    guint i;
    gchar buffer[64];
    
    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "GtkList Example");
    g_signal_connect (G_OBJECT (window), "destroy",
		                  G_CALLBACK (gtk_main_quit),
		                  NULL);
    
    //vbox
    vbox=gtk_vbox_new (FALSE, 5);
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);
    
    //scrolled window 
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_widget_set_size_request (scrolled_window, 250, 150);
    gtk_container_add (GTK_CONTAINER (vbox), scrolled_window);
    gtk_widget_show (scrolled_window);
    
    //list
    gtklist=gtk_list_new ();
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window),
                                          gtklist);
    gtk_widget_show (gtklist);
   

    //list item
    for (i = 0; i < 10; i++) 
    {
				GtkWidget       *label;
				gchar           *string;
				
				sprintf(buffer, _("中文"), i);
				label=gtk_label_new (buffer);
				list_item=gtk_list_item_new ();
				gtk_container_add (GTK_CONTAINER (list_item), label);
				gtk_widget_show (label);
				gtk_container_add (GTK_CONTAINER (gtklist), list_item);
				gtk_widget_show (list_item);
				gtk_label_get (GTK_LABEL (label), &string);
				//g_object_set_data (G_OBJECT (list_item), list_item_data_key, string);
    }
    
    gtk_widget_show (window);
    gtk_main ();*/
    
    return 0;
}
