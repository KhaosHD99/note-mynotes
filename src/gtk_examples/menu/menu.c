
#include <stdio.h>
#include <gtk/gtk.h>

static gint button_press (GtkWidget *, GdkEvent *);
static void menuitem_response (gchar *);

int main( int   argc,
          char *argv[] )
{

    GtkWidget *window;
    GtkWidget *menu;
    GtkWidget *menu_bar;
    GtkWidget *root_menu;
    GtkWidget *menu_items;
    GtkWidget *vbox;
    GtkWidget *button;
    char buf[128];
    int i;

    gtk_init (&argc, &argv);

    /* ����һ���´��� */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 200, 100);
    gtk_window_set_title (GTK_WINDOW (window), "GTK Menu Test");
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (gtk_main_quit), NULL);

    /* ��ʼ���˵���������ס����ԶҲ��Ҫ��
     * gtk_show_widget() ����ʾ�˵������� 
     * ����ǰ����˵���Ĳ˵��������ڳ����"Root Menu"�ϵ��ʱ
     * ���ᵯ���� */
    menu = gtk_menu_new ();

    /* ����������һ��Сѭ��Ϊ"test-menu"���������˵���Ŀ��
     * ע���gtk_menu_append�ĵ��á��������ǽ�һ���еĲ˵���
     * �ӵ����ǵĲ˵��ϡ�ͨ��������Ҳ����ÿ���˵����"clicked"
     * �źŲ�Ϊ������һ���ص������������������ʡ�����Խ�ʡ�ռ䡣 */

    for (i = 0; i < 3; i++)
        {
            /* �����Ƹ��Ƶ�buf. */
            sprintf (buf, "Test-undermenu - %d", i);

            /* ����һ���µĲ˵������Ϊ... */
            menu_items = gtk_menu_item_new_with_label (buf);

            /* ...�������ӵ��˵��� */
            gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_items);

	    /* ���˵��ѡ��ʱ������Ȥ���� */
	    g_signal_connect_swapped (G_OBJECT (menu_items), "activate",
		                      G_CALLBACK (menuitem_response), 
                                      g_strdup (buf));

            /* ��ʾ���� */
            gtk_widget_show (menu_items);
        }

    /* ����Ǹ��˵�������Ϊ��ʾ�ڲ˵����ϵı�ǩ��
     * ���ﲻ�ḽ��һ���źŴ���������Ϊ��ֻ����
     * ������ʱ��������Ĳ˵��� */
    root_menu = gtk_menu_item_new_with_label ("Root Menu");

    gtk_widget_show (root_menu);

    /* ��������ָ��������Ҫ���´�����"menu"��
     * Ϊ"root menu"�Ĳ˵� */
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);

    /* ��һ���˵���һ����ť�ŵ������������ */
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    /* ����һ���˵����԰����˵����������ӵ������� */
    menu_bar = gtk_menu_bar_new ();
    gtk_box_pack_start (GTK_BOX (vbox), menu_bar, FALSE, FALSE, 2);
    gtk_widget_show (menu_bar);

    /* ����һ����ť��������һ�������˵� */
    button = gtk_button_new_with_label ("press me");
    g_signal_connect_swapped (G_OBJECT (button), "event",
	                      G_CALLBACK (button_press), 
                              menu);
    gtk_box_pack_end (GTK_BOX (vbox), button, TRUE, TRUE, 2);
    gtk_widget_show (button);

    /* ���Ѳ˵�����ӵ��˵����� -- �������
     * �����˶�εġ������˵��� =) */
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);

    /* ���������һ����ʾ���ڣ�������һ���������س�������Ļ�ϡ� */
    gtk_widget_show (window);

    gtk_main ();

    return 0;
}

/* ����갴��������Ӧ������widget�������ݽ����Ĳ˵���
 *
 * ע��"widget"�����Ǳ����ݽ����Ĳ˵�������
 * �����µİ�ť��
 */

static gint button_press( GtkWidget *widget,
                          GdkEvent *event )
{

    if (event->type == GDK_BUTTON_PRESS) {
        GdkEventButton *bevent = (GdkEventButton *) event; 
        gtk_menu_popup (GTK_MENU (widget), NULL, NULL, NULL, NULL,
                        bevent->button, bevent->time);
        /* ���ߵ��ô��������Ѿ�����������¼����¼�����(buck)��
         * ����ֹͣ�� */
        return TRUE;
    }

    /* ���ߵ��ô�������û�д�������¼��������������� */
    return FALSE;
}


/* ���˵��ѡ��ʱ��ӡһ���ַ��� */

static void menuitem_response( gchar *string )
{
    printf ("%s\n", string);
}
