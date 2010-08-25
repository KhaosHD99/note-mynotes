
#include <gtk/gtk.h>

#define EVENT_METHOD(i, x) GTK_WIDGET_GET_CLASS(i)->x

#define XSIZE  600
#define YSIZE  400

/* 当点击"close"按钮时，退出应用程序 */
gint close_application( GtkWidget *widget,
                        GdkEvent  *event,
                        gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}

/* 主函数 */
int main( int   argc,
          char *argv[] ) {
    GtkWidget *window, *table, *area, *hrule, *vrule;

    /* 初始化，创建主窗口 */
    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (close_application), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /* 创建一个组装表，绘图区和标尺放在里面 */
    table = gtk_table_new (3, 2, FALSE);
    gtk_container_add (GTK_CONTAINER (window), table);

    area = gtk_drawing_area_new ();
    gtk_widget_set_size_request (GTK_WIDGET (area), XSIZE, YSIZE);
    gtk_table_attach (GTK_TABLE (table), area, 1, 2, 1, 2,
                      GTK_EXPAND|GTK_FILL, GTK_FILL, 0, 0);
    gtk_widget_set_events (area, GDK_POINTER_MOTION_MASK |
                                 GDK_POINTER_MOTION_HINT_MASK);

    /* 水平标尺放在顶部。鼠标移动穿过绘图区时，一个
     * motion_notify_event 被传递给标尺的相应的事件处理函数 */
    hrule = gtk_hruler_new ();
    gtk_ruler_set_metric (GTK_RULER (hrule), GTK_PIXELS);
    gtk_ruler_set_range (GTK_RULER (hrule), 7, 13, 0, 20);
    g_signal_connect_swapped (G_OBJECT (area), "motion_notify_event",
                              G_CALLBACK (EVENT_METHOD (hrule, motion_notify_event)),
                              hrule);
    gtk_table_attach (GTK_TABLE (table), hrule, 1, 2, 0, 1,
                      GTK_EXPAND|GTK_SHRINK|GTK_FILL, GTK_FILL, 0, 0);
    
    /* 垂直标尺放在左边。当鼠标移动穿过绘图区时，一个
     * motion_notify_event 被传递到标尺相应的事件处理函数中 */
    vrule = gtk_vruler_new ();
    gtk_ruler_set_metric (GTK_RULER (vrule), GTK_PIXELS);
    gtk_ruler_set_range (GTK_RULER (vrule), 0, YSIZE, 10, YSIZE );
    g_signal_connect_swapped (G_OBJECT (area), "motion_notify_event",
                              G_CALLBACK (EVENT_METHOD (vrule, motion_notify_event)),
                              vrule);
    gtk_table_attach (GTK_TABLE (table), vrule, 0, 1, 1, 2,
                      GTK_FILL, GTK_EXPAND|GTK_SHRINK|GTK_FILL, 0, 0);

    /* 现在显示所有的构件 */
    gtk_widget_show (area);
    gtk_widget_show (hrule);
    gtk_widget_show (vrule);
    gtk_widget_show (table);
    gtk_widget_show (window);
    gtk_main (); 

    return 0;
}
