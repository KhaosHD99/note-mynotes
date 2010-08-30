#include <gtk/gtk.h>

gint destory(GtkWidget *widget, GtkWidget *window)
{
    gtk_widget_destroy(GTK_WIDGET(window));
    return FALSE;
}

void Button1(GtkWidget *widget, gpointer data)
{
    GtkWidget *window;                        
	GtkWidget *box;
	GtkWidget *button;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);                                    //initailization
    gtk_window_set_title (GTK_WINDOW (window), "i am a subwindow1!");
	
	gtk_widget_set_usize(window, 400, 400);                                           //size
	gtk_window_set_modal(GTK_WINDOW (window), TRUE);
                                                      
	box = gtk_fixed_new();                                                            //container                   
    gtk_container_add (GTK_CONTAINER (window), box);
	
    button = gtk_button_new_with_label ("OK");
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK (destory), window);
    gtk_fixed_put(GTK_FIXED(box), button, 50, 50);
	gtk_widget_show (button);

	button = gtk_button_new_with_label ("Cancel");
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK (destory), window);
    gtk_fixed_put(GTK_FIXED(box), button, 125, 50);
	gtk_widget_show (button); 
	
    gtk_widget_show (box);                                                             //show
    gtk_widget_show (window);  
}

void Button2(GtkWidget *widget, gpointer data)
{
    GtkWidget *window;                        
	GtkWidget *box;
	GtkWidget *button;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);                                   //initailization
    gtk_window_set_title (GTK_WINDOW (window), "i am a subwindow2!");
	
	gtk_widget_set_usize(window, 400, 400);                                          //size
	gtk_window_set_modal(GTK_WINDOW (window), TRUE);                                
                                                      
	box = gtk_fixed_new();                                                            //container                   
    gtk_container_add (GTK_CONTAINER (window), box);

	button = gtk_button_new_with_label ("OK");
	g_signal_connect(G_OBJECT (button),"clicked", G_CALLBACK (destory), window);
    gtk_fixed_put(GTK_FIXED(box), button, 50, 50);
	gtk_widget_show (button); 

	button = gtk_button_new_with_label ("Cancel");
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK (destory), window);
    gtk_fixed_put(GTK_FIXED(box), button, 125, 50);
	gtk_widget_show (button); 
	
	gtk_widget_show (box);                                                             //show
    gtk_widget_show (window);  
}

void Button3(GtkWidget *widget, gpointer data)
{
    GtkWidget *window;                        
	GtkWidget *box;
	GtkWidget *button;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);                                    //initailization
    gtk_window_set_title (GTK_WINDOW (window), "i am a subwindow3!");
	
	gtk_widget_set_usize(window, 400, 400);                                          //size
	gtk_window_set_modal(GTK_WINDOW (window), TRUE);
                                                      
	box = gtk_fixed_new();                                                            //container                   
    gtk_container_add (GTK_CONTAINER (window), box);

	button = gtk_button_new_with_label ("OK");
	g_signal_connect(G_OBJECT (button),"clicked", G_CALLBACK (destory), window);
    gtk_fixed_put(GTK_FIXED(box), button, 50, 50);
	gtk_widget_show (button);        

	button = gtk_button_new_with_label ("Cancel");
	g_signal_connect(G_OBJECT(button),"clicked", G_CALLBACK (destory), window);
    gtk_fixed_put(GTK_FIXED(box), button, 125, 50);
	gtk_widget_show (button); 

	gtk_widget_show (box);                                                              //show
    gtk_widget_show (window);  
}



int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box1;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);                                    //initailization
    gtk_window_set_title (GTK_WINDOW (window), "test!");

    gtk_widget_set_usize(window, 500, 480);                                             //window size
    gtk_window_set_modal(GTK_WINDOW (window), TRUE);                                    

    box1 = gtk_fixed_new ();                                                            //container        
    gtk_container_add(GTK_CONTAINER (window), box1);
	
    button = gtk_button_new_with_label ("button1");                                      //button
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (Button1), "button1");
    gtk_fixed_put (GTK_FIXED(box1), button, 50, 50);
    gtk_widget_show (button); 
	
	button = gtk_button_new_with_label ("button2");
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (Button2), "button2");
    gtk_fixed_put (GTK_FIXED(box1), button, 50, 150);
    gtk_widget_show (button); 

	button = gtk_button_new_with_label ("button3");
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (Button3), "button3");
    gtk_fixed_put (GTK_FIXED(box1), button, 50, 250);
    gtk_widget_show (button);
                                                                
    gtk_widget_show (box1);                                                               //show
    gtk_widget_show (window);       
    gtk_main ();

    return 0;
}
