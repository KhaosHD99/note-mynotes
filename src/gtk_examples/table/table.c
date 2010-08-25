
#include <gtk/gtk.h>

/* ���ǵĻص���
 * ����������������ݱ���ӡ����׼��� */
void callback( GtkWidget *widget,
               gpointer   data )
{
    g_print ("Hello again - %s was pressed\n", (char *) data);
}

/* ����ص��˳����� */
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
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *table;

    gtk_init (&argc, &argv);

    /* ����һ���´��� */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* ���ô��ڱ��� */
    gtk_window_set_title (GTK_WINDOW (window), "Table");

    /* Ϊdelete_event����һ�������˳�GTK�Ĵ������� */
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);

    /* ���ô��ڵı߿��ȡ� */
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);

    /* ����һ��2x2�ı� */
    table = gtk_table_new (2, 2, TRUE);

    /* ����Ž������� */
    gtk_container_add (GTK_CONTAINER (window), table);

    /* ������һ����ť */
    button = gtk_button_new_with_label ("button 1");

    /* �������ť�����ʱ�����ǵ��� "callback" ����������һ��
     * ָ��"button 1"��ָ����Ϊ���Ĳ��� */
    g_signal_connect (G_OBJECT (button), "clicked",
	              G_CALLBACK (callback), (gpointer) "button 1");


    /* ��button 1��������������(quadrant) */
    gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 1, 0, 1);

    gtk_widget_show (button);

    /* �����ڶ�����ť */

    button = gtk_button_new_with_label ("button 2");

    /* �������ť�����ʱ�����ǵ��� "callback" ����������һ��
     * ָ��"button 2"��ָ����Ϊ���Ĳ��� */
    g_signal_connect (G_OBJECT (button), "clicked",
                      G_CALLBACK (callback), (gpointer) "button 2");
    /* ��button 2�������������� */
    gtk_table_attach_defaults (GTK_TABLE (table), button, 1, 2, 0, 1);

    gtk_widget_show (button);

    /* ����"Quit"��ť */
    button = gtk_button_new_with_label ("Quit");

    /* �������ť�����ʱ�����ǵ��� "delete_event" ��������
     * ������˳��� */
    g_signal_connect (G_OBJECT (button), "clicked",
                      G_CALLBACK (delete_event), NULL);

    /* ���˳���ť������������������ */
    gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 2, 1, 2);

    gtk_widget_show (button);

    gtk_widget_show (table);
    gtk_widget_show (window);

    gtk_main ();

    return 0;
}
