
#include <glib.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>

GtkWidget *colorseldlg = NULL;
GtkWidget *drawingarea = NULL;
GdkColor color;

/* ��ɫ�ı��źŵĴ����� */

void color_changed_cb( GtkWidget         *widget,
                       GtkColorSelection *colorsel )
{
  GdkColor ncolor;

  gtk_color_selection_get_current_color (colorsel, &ncolor);
  gtk_widget_modify_bg (drawingarea, GTK_STATE_NORMAL, &ncolor);       
}

/* ��ͼ���¼������� */

gint area_event( GtkWidget *widget,
                 GdkEvent  *event,
                 gpointer   client_data )
{
  gint handled = FALSE;
  gint response;
  GtkColorSelection *colorsel;

  /* ����Ƿ���յ�һ����갴�������¼� */

  if (event->type == GDK_BUTTON_PRESS)
    {
      handled = TRUE;

       /* ������ɫѡ��Ի��� */
      if (colorseldlg == NULL)
        colorseldlg = gtk_color_selection_dialog_new ("Select background color");

      /* ��ȡ��ɫѡ�񹹼� */
      colorsel = GTK_COLOR_SELECTION (GTK_COLOR_SELECTION_DIALOG (colorseldlg)->colorsel);

      gtk_color_selection_set_previous_color (colorsel, &color);
      gtk_color_selection_set_current_color (colorsel, &color);
      gtk_color_selection_set_has_palette (colorsel, TRUE);

      /* Ϊ "color_changed" �ź����ûص����������û���������Ϊ
       * ��ɫѡ�񹹼� */
      g_signal_connect (G_OBJECT (colorsel), "color_changed",
                        G_CALLBACK (color_changed_cb), (gpointer)colorsel);

      /* ��ʾ�Ի��� */
      response = gtk_dialog_run (GTK_DIALOG (colorseldlg));

      if (response == GTK_RESPONSE_OK)
        gtk_color_selection_get_current_color (colorsel, &color);
      else 
        gtk_widget_modify_bg (drawingarea, GTK_STATE_NORMAL, &color);

      gtk_widget_hide (colorseldlg);
    }

  return handled;
}

/* �رա��˳����¼������� */

gint destroy_window( GtkWidget *widget,
                     GdkEvent  *event,
                     gpointer   client_data )
{
  gtk_main_quit ();
  return TRUE;
}

/* ������ */

gint main( gint   argc,
           gchar *argv[] )
{
  GtkWidget *window;

  /* ��ʼ��������ɾȥ�� gtk �йص�������� */

  gtk_init (&argc, &argv);

  /* �����������ڣ����ñ��⣬�Լ������Ƿ������ */

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Color selection test");
  gtk_window_set_policy (GTK_WINDOW (window), TRUE, TRUE, TRUE);

  /* Ϊ "delete" �� "destroy" �¼����ûص������Ա��˳� */

  g_signal_connect (GTK_OBJECT (window), "delete_event",
                    GTK_SIGNAL_FUNC (destroy_window), (gpointer)window);
  
  /* ������ͼ�������óߴ磬������갴���¼� */

  drawingarea = gtk_drawing_area_new ();

  color.red = 0;
  color.blue = 65535;
  color.green = 0;
  gtk_widget_modify_bg (drawingarea, GTK_STATE_NORMAL, &color);       

  gtk_widget_set_size_request (GTK_WIDGET (drawingarea), 200, 200);

  gtk_widget_set_events (drawingarea, GDK_BUTTON_PRESS_MASK);

  g_signal_connect (GTK_OBJECT (drawingarea), "event", 
	            GTK_SIGNAL_FUNC (area_event), (gpointer)drawingarea);
  
  /* ����ͼ����ӵ������У�Ȼ����ʾ���� */

  gtk_container_add (GTK_CONTAINER (window), drawingarea);

  gtk_widget_show (drawingarea);
  gtk_widget_show (window);
  
  /* ����gtk��ѭ��(��������Ӳ��᷵��) */

  gtk_main ();

  /* �������鱩��ı����� */

  return 0;
}
