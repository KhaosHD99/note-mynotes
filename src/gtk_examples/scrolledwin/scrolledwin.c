
#include <stdio.h>
#include <gtk/gtk.h>

void destroy( GtkWidget *widget,
              gpointer   data )
{
    gtk_main_quit ();
}

int main( int   argc,
          char *argv[] )
{
    static GtkWidget *window;
    GtkWidget *scrolled_window;
    GtkWidget *table;
    GtkWidget *button;
    char buffer[32];
    int i, j;
    
    gtk_init (&argc, &argv);
    
    /* ����һ���µĶԻ��򴰿ڣ��������ھͷ������������ */
    window = gtk_dialog_new ();
    g_signal_connect (G_OBJECT (window), "destroy",
		      G_CALLBACK (destroy), NULL);
    gtk_window_set_title (GTK_WINDOW (window), "GtkScrolledWindow example");
    gtk_container_set_border_width (GTK_CONTAINER (window), 0);
    gtk_widget_set_size_request (window, 300, 300);
    
    /* ����һ���µĹ������ڡ� */
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    
    /* �������ĳ��ַ�ʽ������GTK_POLICY_AUTOMATIC ��GTK_POLICY_ALWAYS��
     * ��ΪGTK_POLICY_AUTOMATIC���Զ������Ƿ���Ҫ���ֹ�����
     * ����ΪGTK_POLICY_ALWAYS����һֱ��ʾһ��������
     * ��һ��������ˮƽ���������ڶ����Ǵ�ֱ������ */
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    /* �Ի��򴰿��ڲ�����һ��vbox���� */								
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG(window)->vbox), scrolled_window, 
			TRUE, TRUE, 0);
    gtk_widget_show (scrolled_window);
    
    /* ����һ������10��10�����ӵı�� */
    table = gtk_table_new (10, 10, FALSE);
    
    /* ����x��y������м���Ϊ10���� */
    gtk_table_set_row_spacings (GTK_TABLE (table), 10);
    gtk_table_set_col_spacings (GTK_TABLE (table), 10);
    
    /* �������װ������������ */
    gtk_scrolled_window_add_with_viewport (
                   GTK_SCROLLED_WINDOW (scrolled_window), table);
    gtk_widget_show (table);
    
    /* �򵥵��ڱ���������࿪�ذ�ť��չʾ�������� */
    for (i = 0; i < 10; i++)
       for (j = 0; j < 10; j++) {
          sprintf (buffer, "button (%d,%d)\n", i, j);
	  button = gtk_toggle_button_new_with_label (buffer);
	  gtk_table_attach_defaults (GTK_TABLE (table), button,
	                             i, i+1, j, j+1);
          gtk_widget_show (button);
       }
    
    /* �ڶԻ���ĵײ����һ��"close"��ť */
    button = gtk_button_new_with_label ("close");
    g_signal_connect_swapped (G_OBJECT (button), "clicked",
			      G_CALLBACK (gtk_widget_destroy),
			      window);
    
    /* �ð�ť�ܱ�ȱʡ */
    
    GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window)->action_area), button, TRUE, TRUE, 0);
    
    /* ����ť�̶�Ϊȱʡ��ť��ֻҪ���س������൱�ڵ���������ť */
    gtk_widget_grab_default (button);
    gtk_widget_show (button);
    
    gtk_widget_show (window);
    
    gtk_main();
    
    return 0;
}
