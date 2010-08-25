
#include <stdio.h>
#include <stdlib.h>
#include "gtk/gtk.h"

gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}

/* ����һ��������ť-��ǩ�ĺ���С����ǽ�����Ȥ�Ĳ������ݽ������������
 * ���ǲ���ʾ����У�����ʾ���ڲ������ж����� */
GtkWidget *make_box( gboolean homogeneous,
                     gint     spacing,
		     gboolean expand,
		     gboolean fill,
		     guint    padding ) 
{
    GtkWidget *box;
    GtkWidget *button;
    char padstr[80];
    
    /* �Ժ��ʵ� homogeneous �� spacing ���ô���һ���µĺ���� */
    box = gtk_hbox_new (homogeneous, spacing);
    
    /* �Ժ��ʵ����ô���һϵ�еİ�ť */
    button = gtk_button_new_with_label ("gtk_box_pack");
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_widget_show (button);
    
    button = gtk_button_new_with_label ("(box,");
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_widget_show (button);
    
    button = gtk_button_new_with_label ("button,");
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_widget_show (button);
    
    /* ���� expand ��ֵ����һ������ǩ�İ�ť */
    if (expand == TRUE)
	    button = gtk_button_new_with_label ("TRUE,");
    else
	    button = gtk_button_new_with_label ("FALSE,");
    
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_widget_show (button);
    
    /* ������������ "expand" ������ťһ����������
     * �˼򻯵���ʽ�� */
    button = gtk_button_new_with_label (fill ? "TRUE," : "FALSE,");
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_widget_show (button);
    
    sprintf (padstr, "%d);", padding);
    
    button = gtk_button_new_with_label (padstr);
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_widget_show (button);
    
    return box;
}

int main( int   argc,
          char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *separator;
    GtkWidget *label;
    GtkWidget *quitbox;
    int which;
    
    /* ��ʼ��  */
    gtk_init (&argc, &argv);
    
    if (argc != 2) {
	fprintf (stderr, "usage: packbox num, where num is 1, 2, or 3.\n");
	/* ����ڶ� GTK ������β��������˳�״̬Ϊ 1 �˳��� */
	exit (1);
    }
    
    which = atoi (argv[1]);

    /* �������� */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* ��Ӧ�����Ǽ�ס���� delete_event �źŵ������ڡ����
     * �ʵ���ֱ����Ϊ����Ҫ */
    g_signal_connect (G_OBJECT (window), "delete_event",
		      G_CALLBACK (delete_event), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    /* ���Ǵ���һ������У�vbox���Ѻ������װ������
     * ��ʹ���ǿ��Խ�������ť�ĺ����һ�����ѵ���
     * ��������� */
    box1 = gtk_vbox_new (FALSE, 0);
    
    /* ��ʾ�ĸ�ʾ������Щ��Ӧ�������ͼƬ�� */
    switch (which) {
    case 1:
	/* ����һ���±�ǩ�� */
	label = gtk_label_new ("gtk_hbox_new (FALSE, 0);");
	
	/* ʹ��ǩ�������С����ǽ��ڹ������Բ�����
	 * ����������������ĺ����� */
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0);

	/* ����ǩ��װ������У�vbox box1�����ס�ӵ���������
	 * ����������һ��������һ���������װ�� */
	gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);
	
	/* ��ʾ��ǩ */
	gtk_widget_show (label);
	
	/* �����������ɺеĺ��� - homogeneous = FALSE, spacing = 0,
	 * expand = FALSE, fill = FALSE, padding = 0 */
	box2 = make_box (FALSE, 0, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
	gtk_widget_show (box2);

	/* �����������ɺеĺ��� - homogeneous = FALSE, spacing = 0,
	 * expand = TRUE, fill = FALSE, padding = 0 */
	box2 = make_box (FALSE, 0, TRUE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
	gtk_widget_show (box2);
	
	/* �����ǣ� homogeneous, spacing, expand, fill, padding */
	box2 = make_box (FALSE, 0, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
	gtk_widget_show (box2);
	
	/* ����һ���ָ��ߣ��Ժ����ǻ����ϸ��ѧϰ��Щ�� 
	 * ������ȷʵ�ܼ򵥡� */
	separator = gtk_hseparator_new ();
	
        /* ��װ�ָ��ߵ�����С���ס��Щ����ÿ��������װ
        ����һ������У��������Ǳ���ֱ�ضѵ��� */
	gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
	gtk_widget_show (separator);
	
	/* ������һ���±�ǩ������ʾ���� */
	label = gtk_label_new ("gtk_hbox_new (TRUE, 0);");
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
	gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);
	gtk_widget_show (label);
	
	/* �����ǣ� homogeneous, spacing, expand, fill, padding */
	box2 = make_box (TRUE, 0, TRUE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
	gtk_widget_show (box2);
	
	/* �����ǣ� homogeneous, spacing, expand, fill, padding */
	box2 = make_box (TRUE, 0, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
	gtk_widget_show (box2);
	
	/* ��һ���·ָ��ߡ� */
	separator = gtk_hseparator_new ();
	/* gtk_box_pack_start��������������ǣ�
	 * expand, fill, padding. */
	gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
	gtk_widget_show (separator);
	
	break;

    case 2:

	/* ����һ���±�ǩ����ס box1 ��һ������
	 * �У����� main() ǰ�沿�ִ��� */
	label = gtk_label_new ("gtk_hbox_new (FALSE, 10);");
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
	gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);
	gtk_widget_show (label);
	
	/* �����ǣ� homogeneous, spacing, expand, fill, padding */
	box2 = make_box (FALSE, 10, TRUE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
	gtk_widget_show (box2);
	
	/* �����ǣ� homogeneous, spacing, expand, fill, padding */
	box2 = make_box (FALSE, 10, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
	gtk_widget_show (box2);
	
	separator = gtk_hseparator_new ();
	/* gtk_box_pack_start��������������ǣ�
	 * expand, fill, padding. */
	gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
	gtk_widget_show (separator);
	
	label = gtk_label_new ("gtk_hbox_new (FALSE, 0);");
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
	gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);
	gtk_widget_show (label);
	
	/* �����ǣ� homogeneous, spacing, expand, fill, padding */
	box2 = make_box (FALSE, 0, TRUE, FALSE, 10);
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
	gtk_widget_show (box2);
	
	/* �����ǣ� homogeneous, spacing, expand, fill, padding */
	box2 = make_box (FALSE, 0, TRUE, TRUE, 10);
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
	gtk_widget_show (box2);
	
	separator = gtk_hseparator_new ();
	/* gtk_box_pack_start��������������ǣ� expand, fill, padding�� */
	gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
	gtk_widget_show (separator);
	break;
    
    case 3:

        /* ���ʾ������ gtk_box_pack_end() ���Ҷ��빹
         * �������������ȣ�������ǰ��һ������һ���ºС� */
	box2 = make_box (FALSE, 0, FALSE, FALSE, 0);

	/* ����������ĩ�˵ı�ǩ�� */
	label = gtk_label_new ("end");
	/* �� gtk_box_pack_end()��װ�������������ŵ�
	 * ��make_box()�����ﴴ���ĺ���е��Ҷˡ� */
	gtk_box_pack_end (GTK_BOX (box2), label, FALSE, FALSE, 0);
	/* ��ʾ��ǩ�� */
	gtk_widget_show (label);
	
	/* �� box2 ��װ�� box1 */
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
	gtk_widget_show (box2);
	
	/* ���ڵײ��ķָ��ߡ� */
	separator = gtk_hseparator_new ();
	/* �����ȷ�����÷ָ��ߵĿ��Ϊ400���ص��5���ص�ߡ��������Ǵ���
	 * �ĺ����Ҳ��Ϊ400���ص������"end"��ǩ���ͺ�����������ı�ǩ
	 * �ֿ������򣬺����������й������������ܵ���װ��һ�� */
	gtk_widget_set_size_request (separator, 400, 5);
	/* ���ָ�����װ����main()ǰ�沿�ִ���������У�box1��� */
	gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
	gtk_widget_show (separator);    
    }
    
    /* ������һ���µĺ����.. ��ס����Ҫ�ö��پ����ö��٣� */
    quitbox = gtk_hbox_new (FALSE, 0);
    
    /* �˳���ť�� */
    button = gtk_button_new_with_label ("Quit");
    
    /* ��������ź����ڰ�ť�����ʱ��ֹ���� */
    g_signal_connect_swapped (G_OBJECT (button), "clicked",
			      G_CALLBACK (gtk_main_quit),
			      window);
    /* ����ť��װ��quitbox��
     * gtk_box_pack_start��������������ǣ�
     * expand, fill, padding. */
    gtk_box_pack_start (GTK_BOX (quitbox), button, TRUE, FALSE, 0);
    /* pack the quitbox into the vbox (box1) */
    gtk_box_pack_start (GTK_BOX (box1), quitbox, FALSE, FALSE, 0);
    
    /* �����ڰ������������й���������У�box1����װ�������ڡ� */
    gtk_container_add (GTK_CONTAINER (window), box1);
    
    /* ����ʾʣ�µ����ж��� */
    gtk_widget_show (button);
    gtk_widget_show (quitbox);
    
    gtk_widget_show (box1);
    /* �����ʾ���ڣ��������ж���һ���Գ��֡� */
    gtk_widget_show (window);
    
    /* ��Ȼ���������ǵ��������� */
    gtk_main ();

    /* �� gtk_main_quit() ������ʱ����Ȩ(Control)���ص�
     * �������exit()��ʹ��ʱ�����ᡣ */
    
    return 0;
}
