
#include <gtk/gtk.h>

/* �����¸Ľ��Ļص����������׼���(stdout)��ӡ���ݸ��ú��������ݡ�*/
void callback( GtkWidget *widget,
               gpointer   data )
{
    g_print ("Hello again - %s was pressed\n", (gchar *) data);
}

/* ��һ���ص����� */
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
    /* GtkWidget �ǹ����Ĵ洢���� */
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box1;

    /* ������������е� GTK ����Ҫ���á��������������н������������͵��ó����С�*/
    gtk_init (&argc, &argv);

    /* ����һ���´��� */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* ����һ���µĵ��ã����ô��ڱ���Ϊ"Hello Buttons!" */
    gtk_window_set_title (GTK_WINDOW (window), "Hello Buttons!");

    /* ��������Ϊdelete_event������һ����������*/
    g_signal_connect (G_OBJECT (window), "delete_event",
		      G_CALLBACK (delete_event), NULL);

    /* ���ô��ڱ߿�Ŀ�� */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /* ���Ǵ�����һ����װ�С�����μ�����װ���½ڡ�
     * ���ǿ�������װ�У���������Ϊ���й����Ĺ��ߡ�*/
    box1 = gtk_hbox_new (FALSE, 0);

    /* ����װ�з����������С�*/
    gtk_container_add (GTK_CONTAINER (window), box1);

    /* ����һ����ǩΪ"Button 1"���°�ť��*/
    button = gtk_button_new_with_label ("Button 1");
    
    /* ���ûص�������*/
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (callback), "button 1");

    /* ���ǰѰ�ť���벻�ɼ�����װ�У�����Ϻ��Ѿ������봰���С�*/
    gtk_box_pack_start (GTK_BOX(box1), button, TRUE, TRUE, 0);

    /* ����Ϊ�����ť����׼����������ˣ�������ʾ���ˡ�*/
    gtk_widget_show (button);

    /* ͬ�������ڶ�����ť��*/
    button = gtk_button_new_with_label ("Button 2");

    /* �Բ�ͬ�Ĳ���������ͬ�Ļص���������ָ��"button 2"��ָ����档*/
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (callback), "button 2");

    gtk_box_pack_start(GTK_BOX (box1), button, TRUE, TRUE, 0);

    /* ��ʾ��˳�򲢲���Ҫ�����ҽ��������ʾ���ڡ��������ǻ�ͬʱ��ʾ������*/
    gtk_widget_show (button);

    gtk_widget_show (box1);

    gtk_widget_show (window);
    
    /* ͣ������ȴ��¼�������*/
    gtk_main ();

    return 0;
}
