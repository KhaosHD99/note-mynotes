
#include <stdlib.h>
#include <gtk/gtk.h>

/* ����һ���µ�hbox��������һ��ͼ���һ����ǩ��������������ӡ�*/

GtkWidget *xpm_label_box( gchar     *xpm_filename,
                          gchar     *label_text )
{
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;

    /* �������� */
    box = gtk_hbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);

    /* ����һ��ͼ�� */
    image = gtk_image_new_from_file (xpm_filename);

    /* Ϊ��ť����һ����ǩ */
    label = gtk_label_new (label_text);

    /* ��ͼ��ͱ�ǩ��������� */
    gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 3);

    gtk_widget_show (image);
    gtk_widget_show (label);

    return box;
}

/* Our usual callback function */
void callback( GtkWidget *widget,
               gpointer   data )
{
    g_print ("Hello again - %s was pressed\n", (char *) data);
}

int main( int   argc,
          char *argv[] )
{
    /* GtkWidget �ǹ����Ĵ洢���� */
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box;

    gtk_init (&argc, &argv);

    /* ����һ���´��� */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title (GTK_WINDOW (window), "Pixmap'd Buttons!");

    /* �����еĴ�������һ����һ�������⡣*/
    g_signal_connect (G_OBJECT (window), "destroy",
	              G_CALLBACK (gtk_main_quit), NULL);

    g_signal_connect (G_OBJECT (window), "delete_event",
	 	      G_CALLBACK (gtk_main_quit), NULL);

    /* ���ô��ڱ߿�Ŀ�ȡ�*/
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /* ����һ���µİ�ť */
    button = gtk_button_new ();

    /* ���Ӱ�ť�� "clicked" �ź������ǵĻص����� */
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (callback), (gpointer) "cool button");

    /* �������ǵĺ��Ӵ������� */
    box = xpm_label_box ("info.xpm", "cool button");

    /* ��ʾ���еĹ��� */
    gtk_widget_show (box);

    gtk_container_add (GTK_CONTAINER (button), box);

    gtk_widget_show (button);

    gtk_container_add (GTK_CONTAINER (window), button);

    gtk_widget_show (window);

    /* ͣ������ȴ���Ϣ�� */
    gtk_main ();

    return 0;
}
