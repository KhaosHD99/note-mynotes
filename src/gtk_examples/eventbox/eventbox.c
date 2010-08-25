
#include <stdlib.h>
#include <gtk/gtk.h>

int main( int argc,
          char *argv[] )
{
    GtkWidget *window;
    GtkWidget *event_box;
    GtkWidget *label;
    
    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_title (GTK_WINDOW (window), "Event Box");
    
    g_signal_connect (G_OBJECT (window), "destroy",
	              G_CALLBACK (exit), NULL);
    
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    /* 创建一个事件盒，然后将它加到顶级窗口上 */
    
    event_box = gtk_event_box_new ();
    gtk_container_add (GTK_CONTAINER (window), event_box);
    gtk_widget_show (event_box);
    
    /* 创建一个长标签 */
    
    label = gtk_label_new ("Click here to quit, quit, quit, quit, quit");
    gtk_container_add (GTK_CONTAINER (event_box), label);
    gtk_widget_show (label);
    
    /* 将标签剪裁短。 */
    gtk_widget_set_size_request (label, 110, 20);
    
    /* 为它绑定一个动作 */
    gtk_widget_set_events (event_box, GDK_BUTTON_PRESS_MASK);
    g_signal_connect (G_OBJECT (event_box), "button_press_event",
	              G_CALLBACK (exit), NULL);
    
    /* 又是一个要有 X 窗口的东西... */  
       //译者注： 要设置鼠标式样也要有 X 窗口。gtk_widget_realize使构件在没有show之前就形成 X 窗口。
    
    gtk_widget_realize (event_box);
    gdk_window_set_cursor (event_box->window, gdk_cursor_new (GDK_HAND1));
    
    gtk_widget_show (window);
    
    gtk_main ();
    
    return 0;
}
