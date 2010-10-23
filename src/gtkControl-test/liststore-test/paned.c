#include <stdio.h>
#include <gtk/gtk.h>
   
GtkWidget* create_list(void)
{
	  #if 0
	  //int i;
	  GtkWidget *scrolled_window;
	  GtkBuilder *builder;
	  GtkWidget *window;
    GtkWidget *tree_view;
    GtkListStore *listmodel;
    GtkTreeIter iter;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;
    
    //builder
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "list-store.glade", NULL);
	  
	  //window
	  scrolled_window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
	  tree_view = GTK_WIDGET(gtk_builder_get_object(builder, "treeview1"));
	  //listmodel = (GtkListStore *)gtk_builder_get_object(builder, "liststore1");
	  //listmodel = gtk_list_store_new(1, G_TYPE_STRING);
	  
	  // gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(listmodel));
	  
	  gtk_widget_show(tree_view);
	  
	  /*for (i = 0; i < 10; i++) 
    {
    		gchar *msg = g_strdup_printf("Message #%d", i);
        gtk_list_store_append(GTK_LIST_STORE(listmodel), &iter);
        gtk_list_store_set(GTK_LIST_STORE(listmodel), 
	                         &iter,
                           0, msg,
	                         -1);
	      g_free(msg);
    }*/
   
    //cell = gtk_cell_renderer_text_new();

   // column = gtk_tree_view_column_new_with_attributes ("Message",
 //                                                      cell,
      //                                                 "text", 0,
       //                                                NULL);
  
   // gtk_tree_view_append_column(GTK_TREE_VIEW (tree_view),
	 // 		                         GTK_TREE_VIEW_COLUMN (column));
	  #endif
	  
	  #if 0
    int i;
    GtkWidget *scrolled_window;
    GtkWidget *tree_view;
    GtkListStore *listmodel;
    GtkTreeIter iter;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;

    //scroll when need
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
				                           GTK_POLICY_AUTOMATIC, 
				                           GTK_POLICY_AUTOMATIC);
   
    listmodel = gtk_list_store_new(1, G_TYPE_STRING);
    tree_view = gtk_tree_view_new();
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), 
                                           tree_view);
    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(listmodel));
    gtk_widget_show(tree_view);
   
    /* 在窗口中添加一些消息 */
    for (i = 0; i < 10; i++) 
    {
    		gchar *msg = g_strdup_printf("Message #%d", i);
        gtk_list_store_append(GTK_LIST_STORE(listmodel), &iter);
        gtk_list_store_set(GTK_LIST_STORE(listmodel), 
	                         &iter,
                           0, msg,
	                         -1);
	      g_free(msg);
    }
   
    cell = gtk_cell_renderer_text_new();

    column = gtk_tree_view_column_new_with_attributes("Message",
                                                       cell,
                                                       "text", 0,
                                                       NULL);
  
    gtk_tree_view_append_column(GTK_TREE_VIEW (tree_view),
	  		                         GTK_TREE_VIEW_COLUMN (column));
    #endif
    
    return NULL;
}
   
/* 向文本构件中添加一些文本 - 这是当窗口被实例化(realized)时调用的回调函数。
 * 我们也可以用 gtk_widget_realize 强行将窗口实例化，但这必须在它的层次关系
 *  确定后(be part of a hierarchy)才行。 */
void insert_text(GtkTextBuffer *buffer)
{
		GtkTextIter iter;
		
		gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);
		
		gtk_text_buffer_insert(buffer, &iter,   
		"From: pathfinder@nasa.gov\n"
		"To: mom@nasa.gov\n"
		"Subject: Made it!\n"
		"\n"
		"We just got in this morning. The weather has been\n"
		"great - clear but cold, and there are lots of fun sights.\n"
		"Sojourner says hi. See you soon.\n"
		" -Path\n", -1);
}
   
/* 创建一个滚动文本区域，用于显示一个"信息" */
GtkWidget *create_text( void )
{
		GtkWidget *scrolled_window;
		GtkWidget *view;
		GtkTextBuffer *buffer;
		
		view = gtk_text_view_new ();
		buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
		
		scrolled_window = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
		   	           GTK_POLICY_AUTOMATIC,
				   GTK_POLICY_AUTOMATIC);
		
		gtk_container_add (GTK_CONTAINER (scrolled_window), view);
		insert_text (buffer);
		
		gtk_widget_show_all (scrolled_window);
		
		return scrolled_window;
}
   
int main(int argc, char *argv[])
{
	  #if 0
    GtkWidget *window;
    GtkWidget *vpaned;
    GtkWidget *list;
    //GtkWidget *text;

    gtk_init (&argc, &argv);
   
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Paned Windows");
    
    g_signal_connect (G_OBJECT (window), "destroy",
	              G_CALLBACK (gtk_main_quit), NULL);
	              
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (GTK_WIDGET (window), 450, 400);

    //vpaned   
    vpaned = gtk_vpaned_new();
    gtk_container_add (GTK_CONTAINER (window), vpaned);
    gtk_widget_show (vpaned);
   
    //list
    list = create_list ();
    gtk_paned_add1 (GTK_PANED (vpaned), list);
    gtk_widget_show (list);
   
    //text
    /*text = create_text ();
    gtk_paned_add2 (GTK_PANED(vpaned), text);
    gtk_widget_show (text);*/
    
    gtk_widget_show (window);
    gtk_main ();
    #endif
    
    #if 1      //builder
    int i;
    GtkWidget *window;
	  GtkBuilder *builder;
	  GtkWidget *button;
    GtkWidget *tree_view;
    GtkListStore *listmodel;
    GtkTreeIter iter;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;
    //GtkTreeIter iter;
    //GtkCellRenderer *cell;
    //GtkTreeViewColumn *column;
    
    gtk_init (&argc, &argv);
    
    //builder
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "list-store.glade", NULL);
	  
	  //window
	  window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
	 // tree_view = gtk_tree_view_new();
	  //gtk_container_add(GTK_CONTAINER (window), tree_view);
	  //listmodel = gtk_list_store_new(1, G_TYPE_STRING);
	  
	  tree_view = GTK_WIDGET(gtk_builder_get_object(builder, "treeview1"));
	  listmodel = (GtkListStore *)gtk_builder_get_object(builder, "liststore1");
	  //listmodel = gtk_list_store_new(1, G_TYPE_STRING);
	  
	  gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(listmodel));
	  //gtk_widget_show(tree_view);
	  
	  /*在窗口中添加一些消息*/
    for (i = 0; i < 10; i++) 
    {
    		gchar *msg = g_strdup_printf("Message #%d", i);
        gtk_list_store_append(GTK_LIST_STORE(listmodel), &iter);
        gtk_list_store_set(GTK_LIST_STORE(listmodel), 
	                         &iter,
                           0, msg,
	                         -1);
	      g_free(msg);
    }
   
   cell = gtk_cell_renderer_text_new();

    column = gtk_tree_view_column_new_with_attributes("Message",
                                                       cell,
                                                       "text", 0,
                                                       NULL);
  
    gtk_tree_view_append_column(GTK_TREE_VIEW (tree_view),
	  		                        GTK_TREE_VIEW_COLUMN (column));
	  
	  gtk_widget_show(window);
    gtk_main ();
    #endif
    
    #if 0          //libglade
    int i;
    GtkWidget *window;
    GtkWidget *scrolled_window;
    GtkWidget *tree_view;
    GtkListStore *listmodel;
    GtkTreeIter iter;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;

    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    //scroll when need
    //scrolled_window = gtk_scrolled_window_new (NULL, NULL);
   // gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
		//		                           GTK_POLICY_AUTOMATIC, 
		//		                           GTK_POLICY_AUTOMATIC);
				                           
    listmodel = gtk_list_store_new(1, G_TYPE_STRING);
    tree_view = gtk_tree_view_new();
    //gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), 
    //                                       tree_view);
    gtk_container_add (GTK_CONTAINER (window), tree_view);
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(listmodel));
    gtk_widget_show(tree_view);
   
    /* 在窗口中添加一些消息 */
    for (i = 0; i < 10; i++) 
    {
    		gchar *msg = g_strdup_printf("Message #%d", i);
        gtk_list_store_append(GTK_LIST_STORE(listmodel), &iter);
        gtk_list_store_set(GTK_LIST_STORE(listmodel), 
	                         &iter,
                           0, msg,
	                         -1);
	      g_free(msg);
    }
   
    cell = gtk_cell_renderer_text_new();

    column = gtk_tree_view_column_new_with_attributes("Message",
                                                       cell,
                                                       "text", 0,
                                                       NULL);
  
    gtk_tree_view_append_column(GTK_TREE_VIEW (tree_view),
	  		                        GTK_TREE_VIEW_COLUMN (column));
	  		                        
	  gtk_widget_show(window);
	  gtk_main ();
    #endif
    
    return 0;
}
