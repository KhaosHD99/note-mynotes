
#include <glib.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>

GtkWidget *colorseldlg = NULL;
GtkWidget *drawingarea = NULL;
GdkColor color;

/* 颜色改变信号的处理函数 */

void color_changed_cb( GtkWidget         *widget,
                       GtkColorSelection *colorsel )
{
  GdkColor ncolor;

  gtk_color_selection_get_current_color (colorsel, &ncolor);
  gtk_widget_modify_bg (drawingarea, GTK_STATE_NORMAL, &ncolor);       
}

/* 绘图区事件处理函数 */

gint area_event( GtkWidget *widget,
                 GdkEvent  *event,
                 gpointer   client_data )
{
  gint handled = FALSE;
  gint response;
  GtkColorSelection *colorsel;

  /* 检查是否接收到一个鼠标按键按下事件 */

  if (event->type == GDK_BUTTON_PRESS)
    {
      handled = TRUE;

       /* 创建颜色选择对话框 */
      if (colorseldlg == NULL)
        colorseldlg = gtk_color_selection_dialog_new ("Select background color");

      /* 获取颜色选择构件 */
      colorsel = GTK_COLOR_SELECTION (GTK_COLOR_SELECTION_DIALOG (colorseldlg)->colorsel);

      gtk_color_selection_set_previous_color (colorsel, &color);
      gtk_color_selection_set_current_color (colorsel, &color);
      gtk_color_selection_set_has_palette (colorsel, TRUE);

      /* 为 "color_changed" 信号设置回调函数，将用户数据设置为
       * 颜色选择构件 */
      g_signal_connect (G_OBJECT (colorsel), "color_changed",
                        G_CALLBACK (color_changed_cb), (gpointer)colorsel);

      /* 显示对话框 */
      response = gtk_dialog_run (GTK_DIALOG (colorseldlg));

      if (response == GTK_RESPONSE_OK)
        gtk_color_selection_get_current_color (colorsel, &color);
      else 
        gtk_widget_modify_bg (drawingarea, GTK_STATE_NORMAL, &color);

      gtk_widget_hide (colorseldlg);
    }

  return handled;
}

/* 关闭、退出的事件处理函数 */

gint destroy_window( GtkWidget *widget,
                     GdkEvent  *event,
                     gpointer   client_data )
{
  gtk_main_quit ();
  return TRUE;
}

/* 主函数 */

gint main( gint   argc,
           gchar *argv[] )
{
  GtkWidget *window;

  /* 初始化，处理并删去跟 gtk 有关的命令参数 */

  gtk_init (&argc, &argv);

  /* 创建顶级窗口，设置标题，以及窗口是否可缩放 */

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Color selection test");
  gtk_window_set_policy (GTK_WINDOW (window), TRUE, TRUE, TRUE);

  /* 为 "delete" 和 "destroy" 事件设置回调函数以便退出 */

  g_signal_connect (GTK_OBJECT (window), "delete_event",
                    GTK_SIGNAL_FUNC (destroy_window), (gpointer)window);
  
  /* 创建绘图区，设置尺寸，捕获鼠标按键事件 */

  drawingarea = gtk_drawing_area_new ();

  color.red = 0;
  color.blue = 65535;
  color.green = 0;
  gtk_widget_modify_bg (drawingarea, GTK_STATE_NORMAL, &color);       

  gtk_widget_set_size_request (GTK_WIDGET (drawingarea), 200, 200);

  gtk_widget_set_events (drawingarea, GDK_BUTTON_PRESS_MASK);

  g_signal_connect (GTK_OBJECT (drawingarea), "event", 
	            GTK_SIGNAL_FUNC (area_event), (gpointer)drawingarea);
  
  /* 将绘图区添加到窗口中，然后显示它们 */

  gtk_container_add (GTK_CONTAINER (window), drawingarea);

  gtk_widget_show (drawingarea);
  gtk_widget_show (window);
  
  /* 进入gtk主循环(这个函数从不会返回) */

  gtk_main ();

  /* 满足性情暴躁的编译器 */

  return 0;
}
