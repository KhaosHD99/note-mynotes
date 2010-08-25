
#include <gtk/gtk.h>

/* 用指定的参数创建一个箭头构件并将它组装到按钮中 */
GtkWidget *create_arrow_button( GtkArrowType  arrow_type,
				GtkShadowType shadow_type )
{
  GtkWidget *button;
  GtkWidget *arrow;

  button = gtk_button_new ();
  arrow = gtk_arrow_new (arrow_type, shadow_type);

  gtk_container_add (GTK_CONTAINER (button), arrow);
  
  gtk_widget_show (button);
  gtk_widget_show (arrow);

  return button;
}

int main( int   argc,
          char *argv[] )
{
  /* GtkWidget 是构件的存储类型 */
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *box;

  /* 初始化 */
  gtk_init (&argc, &argv);

  /* 创建一个新窗口 */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title (GTK_WINDOW (window), "Arrow Buttons");

  /* 对所有的窗口都这样做是一个好主意 */
  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (gtk_main_quit), NULL);

  /* 设置窗口的边框的宽度 */
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* 建一个组装盒以容纳箭头/按钮 */
  box = gtk_hbox_new (FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (box), 2);
  gtk_container_add (GTK_CONTAINER (window), box);

  /* 组装、显示所有的构件 */
  gtk_widget_show (box);

  button = create_arrow_button (GTK_ARROW_UP, GTK_SHADOW_IN);
  gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 3);

  button = create_arrow_button (GTK_ARROW_DOWN, GTK_SHADOW_OUT);
  gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 3);
  
  button = create_arrow_button (GTK_ARROW_LEFT, GTK_SHADOW_ETCHED_IN);
  gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 3);
  
  button = create_arrow_button (GTK_ARROW_RIGHT, GTK_SHADOW_ETCHED_OUT);
  gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 3);
  
  gtk_widget_show (window);
  
  /* 进入主循环，等待用户的动作 */
  gtk_main ();
  
  return 0;
}
