#include <gtk/gtk.h> 
#include <glade/glade.h>

void on_button1_clicked(GtkWidget *widget, gpointer user_data)
{
  
	g_print("Hello again was pressed\n");
}

int main(int argc, char **argv)
{
    /*GladeXML *xml;
    GtkWidget *window;
   
	  gtk_init(&argc, &argv);
	  xml = glade_xml_new("test.xml", NULL, NULL);                     //initialization
	  window = glade_xml_get_widget(xml, "window1");
	
	  glade_xml_signal_autoconnect(xml);                                 //event
	  g_object_unref(G_OBJECT(xml));
	
	  gtk_widget_show(window);                                           //show
	  gtk_main();
	  return 0;*/
	
	
	
	  GtkBuilder      *builder; 
    GtkWidget      *window;
    
    gtk_init (&argc, &argv);
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "test.xml", NULL);
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
    gtk_builder_connect_signals (builder, NULL);
    g_object_unref (G_OBJECT (builder));
        
    gtk_widget_show (window);                
    gtk_main ();
    return 0;
}



