
#include <gtk/gtk.h>

int main( int   argc,
          char *argv[] )
{
  /* GtkWidget �ǹ����Ĵ洢���� */
  GtkWidget *window;
  GtkWidget *frame;

  /* ��ʼ�� */
  gtk_init (&argc, &argv);
    
  /* ����һ���´��� */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Frame Example");

  /* ���������ǽ� "destroy" �¼����ӵ�һ���ص����� */ 
  g_signal_connect (G_OBJECT (window), "destroy",
		    G_CALLBACK (gtk_main_quit), NULL);

  gtk_widget_set_size_request (window, 300, 300);
  /* ���ô��ڵı߿��� */
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* ����һ����� */
  frame = gtk_frame_new (NULL);
  gtk_container_add (GTK_CONTAINER (window), frame);

  /* ���ÿ�ܵı�ǩ */
  gtk_frame_set_label (GTK_FRAME (frame), "GTK Frame Widget");

  /* ����ǩ��λ�ڿ�ܵ��ұ� */
  gtk_frame_set_label_align (GTK_FRAME (frame), 1.0, 0.0);

  /* ���ÿ�ܵķ�� */
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_ETCHED_OUT);

  gtk_widget_show (frame);
  
  /* ��ʾ���� */
  gtk_widget_show (window);
    
  /* �����¼�ѭ�� */
  gtk_main ();
    
  return 0;
}
