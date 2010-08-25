
#include <gtk/gtk.h>

/* ��׼��͵��������һЩȫ�ֱ�������̶������ﹹ����λ�á� */
gint x = 50;
gint y = 50;

/* ����ص���������ť�ƶ����̶���������λ�á� */
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
  /* GtkWidget �ǹ����Ĵ洢���� */
  GtkWidget *window;
  GtkWidget *fixed;
  GtkWidget *button;
  gint i;

  /* ��ʼ�� */
  gtk_init (&argc, &argv);
    
  /* ����һ���´��� */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Fixed Container");

  /* Ϊ���ڵ� "destroy" �¼�����һ���źŴ����� */ 
  g_signal_connect (G_OBJECT (window), "destroy",
		    G_CALLBACK (gtk_main_quit), NULL);
 
  /* ���ô��ڵı߿��� */
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* ����һ���̶����� */
  fixed = gtk_fixed_new ();
  gtk_container_add (GTK_CONTAINER (window), fixed);
  gtk_widget_show (fixed);
  
  for (i = 1 ; i <= 3 ; i++) {
    /* ����һ����ǩΪ"Press me"���°�ť */
    button = gtk_button_new_with_label ("Press me");
  
    /* ����ť���յ� "clicked" �ź�ʱ������ move_button() ��������������̶�
     * ������Ϊ���������� */
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (move_button), fixed);
  
    /* ����ť��װ��һ���̶������Ĵ����� */
    gtk_fixed_put (GTK_FIXED (fixed), button, i*50, i*50);
  
    /* ���һ������ʾ�½��Ĺ��� */
    gtk_widget_show (button);
  }

  /* ��ʾ���� */
  gtk_widget_show (window);
    
  /* �����¼�ѭ�� */
  gtk_main ();
    
  return 0;
}
