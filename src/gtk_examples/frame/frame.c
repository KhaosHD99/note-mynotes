
#include <gtk/gtk.h>

int main( int   argc,
          char *argv[] )
{
  /* GtkWidget 是构件的存储类型 */
  GtkWidget *window;
  GtkWidget *frame;

  /* 初始化 */
  gtk_init (&argc, &argv);
    
  /* 创建一个新窗口 */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Frame Example");

  /* 在这里我们将 "destroy" 事件连接到一个回调函数 */ 
  g_signal_connect (G_OBJECT (window), "destroy",
		    G_CALLBACK (gtk_main_quit), NULL);

  gtk_widget_set_size_request (window, 300, 300);
  /* 设置窗口的边框宽度 */
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* 创建一个框架 */
  frame = gtk_frame_new (NULL);
  gtk_container_add (GTK_CONTAINER (window), frame);

  /* 设置框架的标签 */
  gtk_frame_set_label (GTK_FRAME (frame), "GTK Frame Widget");

  /* 将标签定位在框架的右边 */
  gtk_frame_set_label_align (GTK_FRAME (frame), 1.0, 0.0);

  /* 设置框架的风格 */
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_ETCHED_OUT);

  gtk_widget_show (frame);
  
  /* 显示窗口 */
  gtk_widget_show (window);
    
  /* 进入事件循环 */
  gtk_main ();
    
  return 0;
}
