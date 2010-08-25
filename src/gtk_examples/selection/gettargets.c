
#include <stdlib.h>
#include <gtk/gtk.h>

void selection_received( GtkWidget        *widget, 
                         GtkSelectionData *selection_data, 
                         gpointer          data );

/* 当用户点击"Get Targets"按钮时调用的信息处理函数 */
void get_targets( GtkWidget *widget,
                  gpointer data )
{
  static GdkAtom targets_atom = GDK_NONE;
  GtkWidget *window = (GtkWidget *)data;	

  /* 得到"TARGETS"字符串对应的原子 */
  if (targets_atom == GDK_NONE)
    targets_atom = gdk_atom_intern ("TARGETS", FALSE);

  /* 要求获取主选中区的"TARGETS"形式的目标 */
  gtk_selection_convert (window, GDK_SELECTION_PRIMARY, targets_atom,
			 GDK_CURRENT_TIME);
}

/* 当选中区所有者返回数据时调用的信号处理函数 */
void selection_received( GtkWidget        *widget,
                         GtkSelectionData *selection_data, 
		         gpointer          data )
{
  GdkAtom *atoms;
  GList *item_list;
  int i;

  /* **** 重要 **** 检测获取信息是否成功  */
  if (selection_data->length < 0)
    {
      g_print ("Selection retrieval failed\n");
      return;
    }
  /* 确认得到的数据为原来要求的形式 */
  if (selection_data->type != GDK_SELECTION_TYPE_ATOM)
    {
      g_print ("Selection \"TARGETS\" was not returned as atoms!\n");
      return;
    }
  
  /* 打印接收到的原子 */
  atoms = (GdkAtom *)selection_data->data;

  item_list = NULL;
  for (i = 0; i < selection_data->length / sizeof(GdkAtom); i++)
    {
      char *name;
      name = gdk_atom_name (atoms[i]);
      if (name != NULL)
	g_print ("%s\n",name);
      else
	g_print ("(bad atom)\n");
    }

  return;
}

int main( int   argc,
          char *argv[] )
{
  GtkWidget *window;
  GtkWidget *button;
  
  gtk_init (&argc, &argv);

  /* 创建顶级窗口 */

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Event Box");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  g_signal_connect (G_OBJECT (window), "destroy",
	            G_CALLBACK (exit), NULL);

  /* 创建一个按钮，用户按它以获取目标 */

  button = gtk_button_new_with_label ("Get Targets");
  gtk_container_add (GTK_CONTAINER (window), button);

  g_signal_connect (G_OBJECT (button), "clicked",
		    G_CALLBACK (get_targets), window);
  g_signal_connect (G_OBJECT (window), "selection_received",
		    G_CALLBACK (selection_received), NULL);

  gtk_widget_show (button);
  gtk_widget_show (window);
  
  gtk_main ();
  
  return 0;
}
