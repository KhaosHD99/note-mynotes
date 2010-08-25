
#include <gtk/gtk.h>

/* 我准备偷点懒，用一些全局变量储存固定容器里构件的位置。 */
gint x = 50;
gint y = 50;

/* 这个回调函数将按钮移动到固定容器的新位置。 */
void move_button( GtkWidget *widget,
                  GtkWidget *fixed )
{
  x = (x + 30) % 300;
  y = (y + 50) % 300;
  gtk_fixed_move (GTK_FIXED (fixed), widget, x, y); 
}

int main( int   argc,
          char *argv[] )
{
  /* GtkWidget 是构件的存储类型 */
  GtkWidget *window;
  GtkWidget *fixed;
  GtkWidget *button;
  gint i;

  /* 初始化 */
  gtk_init (&argc, &argv);
    
  /* 创建一个新窗口 */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Fixed Container");

  /* 为窗口的 "destroy" 事件设置一个信号处理函数 */ 
  g_signal_connect (G_OBJECT (window), "destroy",
		    G_CALLBACK (gtk_main_quit), NULL);
 
  /* 设置窗口的边框宽度 */
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* 创建一个固定容器 */
  fixed = gtk_fixed_new ();
  gtk_container_add (GTK_CONTAINER (window), fixed);
  gtk_widget_show (fixed);
  
  for (i = 1 ; i <= 3 ; i++) {
    /* 创建一个标签为"Press me"的新按钮 */
    button = gtk_button_new_with_label ("Press me");
  
    /* 当按钮接收到 "clicked" 信号时，调用 move_button() 函数，并把这个固定
     * 容器作为参数传给它 */
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (move_button), fixed);
  
    /* 将按钮组装到一个固定容器的窗口中 */
    gtk_fixed_put (GTK_FIXED (fixed), button, i*50, i*50);
  
    /* 最后一步是显示新建的构件 */
    gtk_widget_show (button);
  }

  /* 显示窗口 */
  gtk_widget_show (window);
    
  /* 进入事件循环 */
  gtk_main ();
    
  return 0;
}
