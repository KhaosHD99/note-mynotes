#include <stdio.h>
#include <gtk/gtk.h>
//#include <stdlib.h>
//#include "phonebookapi.h"
//#include "windowstack.h"
//#include "MessageStack.h"

#if 1
GtkWidget *rootWindow;
GtkWidget *childWindow;
GtkWidget *childWindow2;
GtkBuilder *builder;

void on_button_hide_clicked(GtkWidget* gtklist, gpointer user_data)
{
		if(rootWindow)
		{
				gtk_widget_hide(childWindow);
		}
		else
				printf("root Window is NULL\n");
		
		gtk_main();
}

void on_button_child_hide_clicked(GtkWidget* gtklist, gpointer user_data)
{
		if(childWindow)
		{
			  printf("childWindow is not NULL\n");
				gtk_widget_hide(childWindow);	
		}
		else
				printf("childWindow is NULL\n");
}

void on_button_child2_hide1_clicked(GtkWidget* gtklist, gpointer user_data)
{
	  printf("childWindow2 event\n");
		gtk_widget_hide(childWindow2);	
}

void on_button_child_clicked(GtkWidget* gtklist, gpointer user_data)
{
	  #if 0
	  printf("show child event\n");
	  GtkWidget *window;
	  GtkWidget *button;
	  
	  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	  gtk_window_set_default_size(GTK_WINDOW(window), 100, 100);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	  
	  button = gtk_button_new ();
	  gtk_container_add (GTK_CONTAINER (window), button);
	  gtk_widget_show(button);
	  
	  if(window)
		{
			  printf("window is not NULL\n");
			 // gtk_widget_hide(rootWindow);	
				gtk_widget_show(window);
		}
		else
				printf("window is NULL\n");
	  
	  gtk_main();
	  #endif
	
	  #if 1
	  if(!childWindow)
	  {
	  	  printf("childWindow is NULL\n");
    		GtkWidget *window;
    		window = GTK_WIDGET(gtk_builder_get_object(builder, "window_child"));
        childWindow = window;
        
    		//g_object_unref(G_OBJECT (builder));
    		gtk_widget_show(childWindow);
    }
    else
    {
    	  printf("window is not NULL\n");
    		gtk_widget_show(childWindow);
    }
    gtk_main();
    #endif
}

int main(int argc, char *argv[])
{
	  #if 1        //builder
	  //creat_window_stack();
    GtkWidget *window;
    GtkWidget *window2;
    GtkWidget *window3;
    
    //builder
    gtk_init (&argc, &argv);
    
    
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "wm.glade", NULL);
	  
	  //window
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_root"));
    //window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window_child"));
    //window3 = GTK_WIDGET(gtk_builder_get_object(builder, "window_child2"));
    
    rootWindow = window;
		//childWindow = window2;
		//childWindow2 = window3;
		
		//put_window_into_stack(rootWindow);
		//put_window_into_stack(childWindow);
		
    //event
    gtk_builder_connect_signals(builder, NULL);
    //g_object_unref(G_OBJECT (builder));
    
    gtk_widget_show(rootWindow);
    //gtk_widget_show(childWindow);
    //gtk_widget_show(childWindow2);

    gtk_main();
    #endif
    
    
    #if 0
    GtkWidget *window;
    GtkWidget *window2;
	  GtkWidget *button;

    gtk_init (&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    //window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
    //gtk_window_set_default_size(GTK_WINDOW(window2), 200, 200);
    //gtk_window_set_position(GTK_WINDOW(window2),GTK_WIN_POS_CENTER);

    
    button = gtk_button_new ();

    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (on_button_child_clicked), NULL);
	  
	  gtk_widget_show (button);
	  gtk_container_add (GTK_CONTAINER (window), button);
    gtk_widget_show(window);
    //gtk_widget_show(window2);

    gtk_main();
    #endif    
    
    return 0;
}
#endif
