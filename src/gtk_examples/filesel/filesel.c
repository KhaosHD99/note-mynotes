
#include <gtk/gtk.h>

/* ����ļ�������������ӡ������̨(console)�� */
void file_ok_sel( GtkWidget        *w,
                  GtkFileSelection *fs )
{
    g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
}

int main( int   argc,
          char *argv[] )
{
    GtkWidget *filew;
    
    gtk_init (&argc, &argv);
    
    /* ����һ���µ��ļ�ѡ�񹹼� */
    filew = gtk_file_selection_new ("File selection");
    
    g_signal_connect (G_OBJECT (filew), "destroy",
	              G_CALLBACK (gtk_main_quit), NULL);
    /* Ϊok_button��ť���ûص����������ӵ�file_ok_sel function���� */
    g_signal_connect (G_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),
		      "clicked", 
                      G_CALLBACK (file_ok_sel), filew);
    
    /* Ϊcancel_button���ûص����������ٹ��� */
    g_signal_connect_swapped (G_OBJECT (GTK_FILE_SELECTION (filew)->cancel_button),
	                      "clicked", 
                              G_CALLBACK (gtk_widget_destroy), filew);
    
    /* �����ļ������������һ���ļ�����Ի������Ǹ���һ��ȱʡ�ļ��� */
    gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew), 
				     "penguin.png");
    
    gtk_widget_show (filew);
    gtk_main ();
    return 0;
}
