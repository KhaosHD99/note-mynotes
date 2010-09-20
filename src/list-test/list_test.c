#include <gtk/gtk.h>
#include <stdio.h>
#include <glib/gi18n.h>
#include <locale.h>

#define PACKAGE "main" //软件包名  最后生成的.mo文件名应该命名为这个
#define LOCALEDIR "./locale" //locale所在目录

const gchar *list_item_data_key="list_item_data";

static void  sigh_print_selection( GtkWidget *gtklist,
                                   gpointer   func_data);

static void  sigh_button_event( GtkWidget      *gtklist,
                                GdkEventButton *event,
                                GtkWidget      *frame );

gint main(int argc, gchar *argv[])
{
	  setlocale(LC_ALL, "en_US.UTF-8");
	//  textdomain (PACKAGE);
   // bindtextdomain (PACKAGE, LOCALEDIR);
    
   // bindtextdomain (PACKAGE, LOCALEDIR);
    //bind_textdomain_codeset (PACKAGE, "UTF-8");
   // textdomain (PACKAGE);

     gtk_set_locale(); 
    
    bindtextdomain ("main", "./locale"); 
      textdomain ("main"); 

    
    GtkWidget *separator;
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *scrolled_window;
    GtkWidget *frame;
    GtkWidget *gtklist;
    GtkWidget *button;
    GtkWidget *list_item;
    GList *dlist;
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
   // g_signal_connect (G_OBJECT (gtklist), "selection_changed",
     //                 G_CALLBACK (sigh_print_selection),
   //                   NULL);
    
 
    //list item
    for (i = 0; i < 5; i++) 
    {
				GtkWidget       *label;
				gchar           *string;
				
				sprintf(buffer, "徐镇杰", i);
				label=gtk_label_new (buffer);
				list_item=gtk_list_item_new ();
				gtk_container_add (GTK_CONTAINER (list_item), label);
				gtk_widget_show (label);
				gtk_container_add (GTK_CONTAINER (gtklist), list_item);
				gtk_widget_show(list_item);
				gtk_label_get (GTK_LABEL (label), &string);
				g_object_set_data (G_OBJECT (list_item), list_item_data_key, string);
    }
    
    gtk_widget_show (window);
    gtk_main ();
    
    return 0;
}
