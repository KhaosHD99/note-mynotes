
#include <gtk/gtk.h>

/* 我们新改进的回调函数。向标准输出(stdout)打印传递给该函数的数据。*/
void callback( GtkWidget *widget,
               gpointer   data )
{
    g_print ("Hello again - %s was pressed\n", (gchar *) data);
}

/* 另一个回调函数 */
gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}

int main( int   argc,
          char *argv[] )
{
    /* GtkWidget 是构件的存储类型 */
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box1;

    /* 这个函数在所有的 GTK 程序都要调用。参数由命令行中解析出来并且送到该程序中。*/
    gtk_init (&argc, &argv);

    /* 创建一个新窗口 */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* 这是一个新的调用，设置窗口标题为"Hello Buttons!" */
    gtk_window_set_title (GTK_WINDOW (window), "Hello Buttons!");

    /* 在这我们为delete_event设置了一个处理函数。*/
    g_signal_connect (G_OBJECT (window), "delete_event",
		      G_CALLBACK (delete_event), NULL);

    /* 设置窗口边框的宽度 */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /* 我们创建了一个组装盒。详情参见“组装”章节。
     * 我们看不见组装盒，它仅被作为排列构件的工具。*/
    box1 = gtk_hbox_new (FALSE, 0);

    /* 把组装盒放入主窗口中。*/
    gtk_container_add (GTK_CONTAINER (window), box1);

    /* 创建一个标签为"Button 1"的新按钮。*/
    button = gtk_button_new_with_label ("Button 1");
    
    /* 设置回调函数。*/
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (callback), "button 1");

    /* 我们把按钮放入不可见的组装盒，该组合盒已经被放入窗口中。*/
    gtk_box_pack_start (GTK_BOX(box1), button, TRUE, TRUE, 0);

    /* 我们为这个按钮做的准备工作完成了，可以显示它了。*/
    gtk_widget_show (button);

    /* 同样创建第二个按钮。*/
    button = gtk_button_new_with_label ("Button 2");

    /* 以不同的参数调用相同的回调函数，用指向"button 2"的指针代替。*/
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (callback), "button 2");

    gtk_box_pack_start(GTK_BOX (box1), button, TRUE, TRUE, 0);

    /* 显示的顺序并不重要，但我建议最后显示窗口。这样它们会同时显示出来。*/
    gtk_widget_show (button);

    gtk_widget_show (box1);

    gtk_widget_show (window);
    
    /* 停在这里等待事件发生。*/
    gtk_main ();

    return 0;
}
