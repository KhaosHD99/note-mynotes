#include<libintl.h>
#include<locale.h>
#include<stdio.h>
#include<gtk/gtk.h>

#define _(String) gettext (String)
#define _t(String1,String2,n) ngettext (String1,String2,n)

const gchar *list_item_data_key="list_item_data";

void on_list1_select_child(GtkWidget *gtklist, gpointer user_data)
{
	  GList   *dlist;
    dlist = GTK_LIST (gtklist)->selection;
    const gchar *item_data_string;
    
    if (!dlist) 
				return;
  
	  item_data_string = g_object_get_data (G_OBJECT (dlist->data),list_item_data_key);
	 	g_print("The selection is %s ", item_data_string);
 	 
    g_print ("\n");
}
 
int main(int argc, char *argv[])
{
	  GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *gtklist;
    GtkWidget *list_item;
    int i;
    char buffer[64];
    
    //builder
    gtk_init (&argc, &argv);
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "list.xml", NULL);
	  
	  //window
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    gtk_window_set_title (GTK_WINDOW (window), "GtkList Example");
    g_signal_connect (G_OBJECT (window), "destroy",
		                  G_CALLBACK (gtk_main_quit),
		                  NULL);
		
    //list
    gtklist = GTK_WIDGET(gtk_builder_get_object(builder, "list1"));
    
    //list item
    for (i = 0; i < 20; i++) 
    {
				GtkWidget       *label;
				char           *string;
				
				sprintf(buffer, "中文%d", i);
				label=gtk_label_new (buffer);
				list_item=gtk_list_item_new ();
				gtk_container_add (GTK_CONTAINER (list_item), label);
				gtk_container_add (GTK_CONTAINER (gtklist), list_item);
				gtk_label_get (GTK_LABEL (label), &string);
				g_object_set_data (G_OBJECT (list_item), list_item_data_key, string);
    }
    
    //event
    gtk_builder_connect_signals (builder, NULL);
    g_object_unref (G_OBJECT (builder));
    
    gtk_widget_show_all (window);
    gtk_main ();
    
    return 0;
}
