
#include <stdlib.h>
#include <gtk/gtk.h>
#include <time.h>

GtkWidget *selection_button;
GtkWidget *selection_widget;

/* 当用户触发选中区时的回调 */
void selection_toggled( GtkWidget *widget,
                        gint      *have_selection )
{
  if (GTK_TOGGLE_BUTTON (widget)->active)
    {
      *have_selection = gtk_selection_owner_set (selection_widget,
						 GDK_SELECTION_PRIMARY,
						 GDK_CURRENT_TIME);
      /* 如果声称选中区失败，则使按钮返回未选中状态 */
      if (!*have_selection)
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), FALSE);
    }
  else
    {
      if (*have_selection)
	{
	  /* 在设置所有者为NULL来清空选中区前，
	   * 先检测自己是不是真正的所有者 */
	  if (gdk_selection_owner_get (GDK_SELECTION_PRIMARY) == widget->window)
	    gtk_selection_owner_set (NULL, GDK_SELECTION_PRIMARY,
				     GDK_CURRENT_TIME);
	  *have_selection = FALSE;
	}
    }
}

/* 当其它应用程序声称选中区时调用 */
gint selection_clear( GtkWidget         *widget,
                      GdkEventSelection *event,
                      gint              *have_selection )
{
  *have_selection = FALSE;
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (selection_button), FALSE);

  return TRUE;
}

/* 将当前时间作为选中区内容提供。 */
void selection_handle( GtkWidget        *widget, 
                       GtkSelectionData *selection_data,
                       guint             info,
                       guint             time_stamp,
                       gpointer          data )
{
  gchar *timestr;
  time_t current_time;

  current_time = time (NULL);
  timestr = asctime (localtime (&current_time)); 
  /* 当我们返回单独一个字符串时，它不必以NULL结尾。
     它将被自动完成 */

  gtk_selection_data_set (selection_data, GDK_SELECTION_TYPE_STRING,
			  8, timestr, strlen (timestr));
}

int main( int   argc,
          char *argv[] )
{
  GtkWidget *window;

  static int have_selection = FALSE;
  
  gtk_init (&argc, &argv);

  /* 创建顶级窗口 */

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Event Box");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  g_signal_connect (G_OBJECT (window), "destroy",
		    G_CALLBACK (exit), NULL);

  /* 创建一个开关按钮作为选中区 */

  selection_widget = gtk_invisible_new ();
  selection_button = gtk_toggle_button_new_with_label ("Claim Selection");
  gtk_container_add (GTK_CONTAINER (window), selection_button);
  gtk_widget_show (selection_button);

  g_signal_connect (G_OBJECT (selection_button), "toggled",
		    G_CALLBACK (selection_toggled), &have_selection);
  g_signal_connect (G_OBJECT (selection_widget), "selection_clear_event",
		    G_CALLBACK (selection_clear), &have_selection);

  gtk_selection_add_target (selection_widget,
			    GDK_SELECTION_PRIMARY,
			    GDK_SELECTION_TYPE_STRING,
		            1);
  g_signal_connect (G_OBJECT (selection_widget), "selection_get",
		    G_CALLBACK (selection_handle), &have_selection);

  gtk_widget_show (selection_button);
  gtk_widget_show (window);
  
  gtk_main ();
  
  return 0;
}
