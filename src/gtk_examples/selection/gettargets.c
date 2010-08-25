
#include <stdlib.h>
#include <gtk/gtk.h>

void selection_received( GtkWidget        *widget, 
                         GtkSelectionData *selection_data, 
                         gpointer          data );

/* ���û����"Get Targets"��ťʱ���õ���Ϣ������ */
void get_targets( GtkWidget *widget,
                  gpointer data )
{
  static GdkAtom targets_atom = GDK_NONE;
  GtkWidget *window = (GtkWidget *)data;	

  /* �õ�"TARGETS"�ַ�����Ӧ��ԭ�� */
  if (targets_atom == GDK_NONE)
    targets_atom = gdk_atom_intern ("TARGETS", FALSE);

  /* Ҫ���ȡ��ѡ������"TARGETS"��ʽ��Ŀ�� */
  gtk_selection_convert (window, GDK_SELECTION_PRIMARY, targets_atom,
			 GDK_CURRENT_TIME);
}

/* ��ѡ���������߷�������ʱ���õ��źŴ����� */
void selection_received( GtkWidget        *widget,
                         GtkSelectionData *selection_data, 
		         gpointer          data )
{
  GdkAtom *atoms;
  GList *item_list;
  int i;

  /* **** ��Ҫ **** ����ȡ��Ϣ�Ƿ�ɹ�  */
  if (selection_data->length < 0)
    {
      g_print ("Selection retrieval failed\n");
      return;
    }
  /* ȷ�ϵõ�������Ϊԭ��Ҫ�����ʽ */
  if (selection_data->type != GDK_SELECTION_TYPE_ATOM)
    {
      g_print ("Selection \"TARGETS\" was not returned as atoms!\n");
      return;
    }
  
  /* ��ӡ���յ���ԭ�� */
  atoms = (GdkAtom *)selection_data->data;

  item_list = NULL;
  for (i = 0; i < selection_data->length / sizeof(GdkAtom); i++)
    {
      char *name;
      name = gdk_atom_name (atoms[i]);
      if (name != NULL)
	g_print ("%s\n",name);
      else
	g_print ("(bad atom)\n");
    }

  return;
}

int main( int   argc,
          char *argv[] )
{
  GtkWidget *window;
  GtkWidget *button;
  
  gtk_init (&argc, &argv);

  /* ������������ */

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Event Box");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  g_signal_connect (G_OBJECT (window), "destroy",
	            G_CALLBACK (exit), NULL);

  /* ����һ����ť���û������Ի�ȡĿ�� */

  button = gtk_button_new_with_label ("Get Targets");
  gtk_container_add (GTK_CONTAINER (window), button);

  g_signal_connect (G_OBJECT (button), "clicked",
		    G_CALLBACK (get_targets), window);
  g_signal_connect (G_OBJECT (window), "selection_received",
		    G_CALLBACK (selection_received), NULL);

  gtk_widget_show (button);
  gtk_widget_show (window);
  
  gtk_main ();
  
  return 0;
}
