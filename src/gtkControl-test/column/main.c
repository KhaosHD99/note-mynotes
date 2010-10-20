#include <stdio.h>
#include <gtk/gtk.h>
//#include "phonebookapi.h"
//#include "windowstack.h"
//#include "MessageStack.h"

GtkBuilder *builder;

static GtkListStore* create_store(void)
{
	GtkListStore *store;
	//store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	store = gtk_builder_get_object(builder, "liststore1");
	
	return store;
}

static GtkTreeModel* fill_store(GtkListStore *store)
{
    int i;
    for(i = 0; i < 3; i++)
	{ 
		GtkTreeIter iter;
        
	    gtk_list_store_append (store, &iter);
	    gtk_list_store_set(store, &iter, 
			               0, "teststr",
			               1, "teststr2",  
			               -1);
	    
		#if 0
		#endif
	}
	return GTK_TREE_MODEL (store);
}

static void set_text (GtkTreeViewColumn *tree_column,
				      GtkCellRenderer   *cell,
				      GtkTreeModel      *model,
				      GtkTreeIter       *iter,
				      gpointer           data)
{   
    #if 1
	char *given_name;
	char *family_name;
	//char strCombine[64];
    
	gtk_tree_model_get(model, iter,
	                 0, &given_name,
	                 1, &family_name,
	                 -1);
    
	//sprintf(strCombine, "%s%s", family_name, given_name);
    
	//printf("name: %s\n", family_name);
	g_object_set(GTK_CELL_RENDERER(cell),
	             "text", "test",
	             NULL);
    #endif
	  //g_free();
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	GtkWidget *window;
	GtkListStore *store;
	GtkTreeModel *tree_model;
	GtkWidget *treeview;
	GtkTreeViewColumn *column;
    GtkCellRenderer *cell_renderer;
	   
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "column.glade", NULL);
    
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_contact"));
	gtk_window_move(GTK_WINDOW(window), 200, 0);
    
    store = create_store();
    tree_model = fill_store(store);
 	treeview = GTK_WIDGET(gtk_builder_get_object(builder, "treeview_list"));
	gtk_tree_view_set_model(treeview, tree_model);
    
    g_object_unref (tree_model);
    
    //column  
    column = GTK_WIDGET(gtk_builder_get_object(builder, "gchar1"));
	//column = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(column, "联系人");
    #if 0
    
	//text cell renderer
	cell_renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_column_pack_start(column,
			       	                cell_renderer,
			       					TRUE);
    
	gtk_tree_view_column_set_cell_data_func(column, cell_renderer,
		                              	    set_text, NULL, NULL);
    
	//bingding column to tree view                              		      
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),
					            column);
    #endif
	gtk_builder_connect_signals(builder, NULL);
	
    gtk_widget_show(window);
    
	gtk_main();
    
    return 0;
}

