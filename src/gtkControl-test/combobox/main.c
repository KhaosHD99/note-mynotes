#include <stdio.h>
#include <gtk/gtk.h>

GtkBuilder *builder;

GtkListStore *store;
GtkTreeModel *tree_model;


enum 
{
  PIXBUF_COL,
  TEXT_COL
};

static gchar *
strip_underscore (const gchar *text)
{
  gchar *p, *q;
  gchar *result;
  
  result = g_strdup (text);
  p = q = result;
  while (*p) 
    {
      if (*p != '_')
	{
	  *q = *p;
	  q++;
	}
      p++;
    }
  *q = '\0';

  return result;
}

static GtkTreeModel *
create_stock_icon_store (void)
{
  gchar *stock_id[6] = {
    GTK_STOCK_DIALOG_WARNING,
    GTK_STOCK_STOP,
    GTK_STOCK_NEW,
    GTK_STOCK_CLEAR,
    NULL,
    GTK_STOCK_OPEN    
  };

  GtkStockItem item;
  GdkPixbuf *pixbuf;
  GtkWidget *cellview;
  GtkTreeIter iter;
  GtkListStore *store;
  gchar *label;
  gint i;

  cellview = gtk_cell_view_new ();
  
  store = gtk_list_store_new (2, GDK_TYPE_PIXBUF, G_TYPE_STRING);

  for (i = 0; i < G_N_ELEMENTS (stock_id); i++)
    {
      if (stock_id[i])
	{
	  pixbuf = gtk_widget_render_icon (cellview, stock_id[i],
					   GTK_ICON_SIZE_BUTTON, NULL);
	  gtk_stock_lookup (stock_id[i], &item);
	  label = strip_underscore (item.label);
	  gtk_list_store_append (store, &iter);
	  gtk_list_store_set (store, &iter,
			      PIXBUF_COL, pixbuf,
			      TEXT_COL, label,
			      -1);
	  g_object_unref (pixbuf);
	  g_free (label);
	}
      else
	{
	  gtk_list_store_append (store, &iter);
	  gtk_list_store_set (store, &iter,
			      PIXBUF_COL, NULL,
			      TEXT_COL, "separator",
			      -1);
	}
    }

  gtk_widget_destroy (cellview);
  
  return GTK_TREE_MODEL (store);
}

/* A GtkCellLayoutDataFunc that demonstrates how one can control
 * sensitivity of rows. This particular function does nothing 
 * useful and just makes the second row insensitive.
 */
static void
set_sensitive (GtkCellLayout   *cell_layout,
		       GtkCellRenderer *cell,
		       GtkTreeModel    *tree_model,
		       GtkTreeIter     *iter,
		       gpointer         data)
{
  GtkTreePath *path;
  gint *indices;
  gboolean sensitive;

  path = gtk_tree_model_get_path (tree_model, iter);
  indices = gtk_tree_path_get_indices (path);
  sensitive = indices[0] != 1;
  gtk_tree_path_free (path);

  g_object_set (cell, "sensitive", sensitive, NULL);
}

/* A GtkTreeViewRowSeparatorFunc that demonstrates how rows can be
 * rendered as separators. This particular function does nothing 
 * useful and just turns the fourth row into a separator.
 */
static gboolean
is_separator (GtkTreeModel *model,
	      GtkTreeIter  *iter,
	      gpointer      data)
{
  GtkTreePath *path;
  gboolean result;

  path = gtk_tree_model_get_path (model, iter);
  result = gtk_tree_path_get_indices (path)[0] == 4;
  gtk_tree_path_free (path);

  return result;
}

static GtkTreeModel *
create_capital_store (void)
{
  struct {
    gchar *group;
    gchar *capital;
  } capitals[] = {
    { "A - B", NULL }, 
    { NULL, "Albany" },
    { NULL, "Annapolis" },
    { NULL, "Atlanta" },
    { NULL, "Augusta" }, 
    { NULL, "Austin" },
    { NULL, "Baton Rouge" },
    { NULL, "Bismarck" },
    { NULL, "Boise" },
    { NULL, "Boston" },
    { "C - D", NULL },
    { NULL, "Carson City" },
    { NULL, "Charleston" },
    { NULL, "Cheyenne" },
    { NULL, "Columbia" },
    { NULL, "Columbus" },
    { NULL, "Concord" },
    { NULL, "Denver" },
    { NULL, "Des Moines" },
    { NULL, "Dover" },
    { "E - J", NULL },
    { NULL, "Frankfort" },
    { NULL, "Harrisburg" },
    { NULL, "Hartford" },
    { NULL, "Helena" },
    { NULL, "Honolulu" },
    { NULL, "Indianapolis" },
    { NULL, "Jackson" },
    { NULL, "Jefferson City" },
    { NULL, "Juneau" },
    { "K - O" },
    { NULL, "Lansing" },
    { NULL, "Lincoln" },
    { NULL, "Little Rock" },
    { NULL, "Madison" },
    { NULL, "Montgomery" },
    { NULL, "Montpelier" },
    { NULL, "Nashville" },
    { NULL, "Oklahoma City" },
    { NULL, "Olympia" },
    { NULL, "P - S" },
    { NULL, "Phoenix" },
    { NULL, "Pierre" },
    { NULL, "Providence" },
    { NULL, "Raleigh" },
    { NULL, "Richmond" },
    { NULL, "Sacramento" },
    { NULL, "Salem" },
    { NULL, "Salt Lake City" },
    { NULL, "Santa Fe" },
    { NULL, "Springfield" },
    { NULL, "St. Paul" },
    { "T - Z", NULL },
    { NULL, "Tallahassee" },
    { NULL, "Topeka" },
    { NULL, "Trenton" },
    { NULL, NULL }
  };
  
	GtkTreeIter iter, iter2;
	GtkTreeStore *store;
	gint i;

 	store = gtk_tree_store_new (1, G_TYPE_STRING);
  
 	for (i = 0; capitals[i].group || capitals[i].capital; i++)
	{
	  if (capitals[i].group)
	{
	  gtk_tree_store_append (store, &iter, NULL);
	  gtk_tree_store_set (store, &iter, 0, capitals[i].group, -1);
	}
	  else if (capitals[i].capital)
	{
	  gtk_tree_store_append (store, &iter2, &iter);
	  gtk_tree_store_set (store, &iter2, 0, capitals[i].capital, -1);
	}
	}
  
  	return GTK_TREE_MODEL (store);
}

static void
is_capital_sensitive (GtkCellLayout   *cell_layout,
		      GtkCellRenderer *cell,
		      GtkTreeModel    *tree_model,
		      GtkTreeIter     *iter,
		      gpointer         data)
{
	gboolean sensitive;

	sensitive = !gtk_tree_model_iter_has_child (tree_model, iter);

	g_object_set (cell, "sensitive", sensitive, NULL);
}

static void
fill_combo_entry (GtkWidget *entry)
{
	gtk_combo_box_append_text (GTK_COMBO_BOX (entry), "One");
	gtk_combo_box_append_text (GTK_COMBO_BOX (entry), "Two");
	gtk_combo_box_append_text (GTK_COMBO_BOX (entry), "2\302\275");
	gtk_combo_box_append_text (GTK_COMBO_BOX (entry), "Three");
}

/* A simple validating entry */

#define TYPE_MASK_ENTRY             (mask_entry_get_type ())
#define MASK_ENTRY(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MASK_ENTRY, MaskEntry))
#define MASK_ENTRY_CLASS(vtable)    (G_TYPE_CHECK_CLASS_CAST ((vtable), TYPE_MASK_ENTRY, MaskEntryClass))
#define IS_MASK_ENTRY(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MASK_ENTRY))
#define IS_MASK_ENTRY_CLASS(vtable) (G_TYPE_CHECK_CLASS_TYPE ((vtable), TYPE_MASK_ENTRY))
#define MASK_ENTRY_GET_CLASS(inst)  (G_TYPE_INSTANCE_GET_CLASS ((inst), TYPE_MASK_ENTRY, MaskEntryClass))


typedef struct _MaskEntry MaskEntry;
struct _MaskEntry
{
  GtkEntry entry;
  gchar *mask;
};

typedef struct _MaskEntryClass MaskEntryClass;
struct _MaskEntryClass
{
  GtkEntryClass parent_class;
};


static void mask_entry_editable_init (GtkEditableClass *iface);

G_DEFINE_TYPE_WITH_CODE (MaskEntry, mask_entry, GTK_TYPE_ENTRY,
			 						G_IMPLEMENT_INTERFACE (GTK_TYPE_EDITABLE,
									mask_entry_editable_init));

static void mask_entry_set_background (MaskEntry *entry)
{
  static const GdkColor error_color = { 0, 65535, 60000, 60000 };

  if (entry->mask)
    {
      if (!g_regex_match_simple (entry->mask, gtk_entry_get_text (GTK_ENTRY (entry)), 0, 0))
	{
	  gtk_widget_modify_base (GTK_WIDGET (entry), GTK_STATE_NORMAL, &error_color);
	  return;
	}
    }

  gtk_widget_modify_base (GTK_WIDGET (entry), GTK_STATE_NORMAL, NULL);
}


static void mask_entry_changed (GtkEditable *editable)
{
  mask_entry_set_background (MASK_ENTRY (editable));
}


static void mask_entry_init (MaskEntry *entry)
{
  entry->mask = NULL;
}


static void mask_entry_class_init (MaskEntryClass *klass)
{ }


static void mask_entry_editable_init (GtkEditableClass *iface)
{
  iface->changed = mask_entry_changed;
}


GtkWidget *do_combobox (GtkWidget *do_widget)
{
  static GtkWidget *window = NULL;
  GtkWidget *vbox, *frame, *box, *combo, *entry;
  GtkTreeModel *model;
  GtkCellRenderer *renderer;
  GtkTreePath *path;
  GtkTreeIter iter;

  if (!window)
  {
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_screen (GTK_WINDOW (window),
                           gtk_widget_get_screen (do_widget));
    gtk_window_set_title (GTK_WINDOW (window), "Combo boxes");
   
    g_signal_connect (window, "destroy",
                      G_CALLBACK (gtk_widget_destroyed),
                      &window);
    
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    vbox = gtk_vbox_new (FALSE, 2);
    gtk_container_add (GTK_CONTAINER (window), vbox);

    /* A combobox demonstrating cell renderers, separators and
     *  insensitive rows 
     */
    frame = gtk_frame_new ("Some stock icons");
    gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);
    
    box = gtk_vbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 5);
    gtk_container_add (GTK_CONTAINER (frame), box);
    
    model = create_stock_icon_store ();
    combo = gtk_combo_box_new_with_model(model);
    g_object_unref (model);
    gtk_container_add (GTK_CONTAINER (box), combo);
    
    renderer = gtk_cell_renderer_pixbuf_new ();
    gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), renderer, FALSE);
    gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo), renderer,
				    "pixbuf", PIXBUF_COL, 
				    NULL);

    gtk_cell_layout_set_cell_data_func (GTK_CELL_LAYOUT (combo),
					renderer,
					set_sensitive,
					NULL, NULL);
    
    renderer = gtk_cell_renderer_text_new ();
    gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), renderer, TRUE);
    gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo), renderer,
				    "text", TEXT_COL,
				    NULL);

    gtk_cell_layout_set_cell_data_func (GTK_CELL_LAYOUT (combo),
					renderer,
					set_sensitive,
					NULL, NULL);

    gtk_combo_box_set_row_separator_func (GTK_COMBO_BOX (combo), 
					  is_separator, NULL, NULL);
    
    gtk_combo_box_set_active (GTK_COMBO_BOX (combo), 0);
    
    /* A combobox demonstrating trees.
     */
    frame = gtk_frame_new ("Where are we ?");
    gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);

    box = gtk_vbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 5);
    gtk_container_add (GTK_CONTAINER (frame), box);
    
    model = create_capital_store ();
    combo = gtk_combo_box_new_with_model (model);
    g_object_unref (model);
    gtk_container_add (GTK_CONTAINER (box), combo);

    renderer = gtk_cell_renderer_text_new ();
    gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), renderer, TRUE);
    gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo), renderer,
				    "text", 0,
				    NULL);
    gtk_cell_layout_set_cell_data_func (GTK_CELL_LAYOUT (combo),
					renderer,
					is_capital_sensitive,
					NULL, NULL);

    path = gtk_tree_path_new_from_indices (0, 8, -1);
    gtk_tree_model_get_iter (model, &iter, path);
    gtk_tree_path_free (path);
    gtk_combo_box_set_active_iter (GTK_COMBO_BOX (combo), &iter);

    /* A GtkComboBoxEntry with validation.
     */
    frame = gtk_frame_new ("Editable");
    gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);
    
    box = gtk_vbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 5);
    gtk_container_add (GTK_CONTAINER (frame), box);
    
    combo = gtk_combo_box_entry_new_text ();
    fill_combo_entry (combo);
    gtk_container_add (GTK_CONTAINER (box), combo);
    
    entry = g_object_new (TYPE_MASK_ENTRY, NULL);
    MASK_ENTRY (entry)->mask = "^([0-9]*|One|Two|2\302\275|Three)$";
     
    gtk_container_remove (GTK_CONTAINER (combo), GTK_BIN (combo)->child);
    gtk_container_add (GTK_CONTAINER (combo), entry);
  
  }

  if (!GTK_WIDGET_VISIBLE (window))
    {
      gtk_widget_show_all (window);
    }
  else
    {    
      gtk_widget_destroy (window);
      window = NULL;
    }

  return window;
}








static GtkListStore* create_store(void)
{
	GtkListStore *store;
	store = gtk_list_store_new(1, G_TYPE_STRING);
	
	return store;
}

static GtkTreeModel* fill_store(GtkListStore *store)
{
    #if 1
    int i;
	//printf("count: %d\n", get_contact_count());
  //  for(i = 0; i < get_contact_count(); i++)
	//{
	   //Contact contact; 
	   GtkTreeIter iter;
	  // memset(&contact, 0, sizeof(Contact));
       //get_contact_by_index(&contact, i);
	   
	   gtk_list_store_append(store, &iter);
	   gtk_list_store_set(store, &iter,
			              0, "test",
			              -1);
//	}
    #endif
	
	return GTK_TREE_MODEL (store);
}

static void set_text (GtkTreeViewColumn *tree_column,
				      GtkCellRenderer   *cell,
				      GtkTreeModel      *model,
				      GtkTreeIter       *iter,
				      gpointer           data)
{
    #if 0
	char *given_name;
	char *family_name;
	char strCombine[64];

	gtk_tree_model_get(model, iter,
	                   0, &family_name,
	                   -1);
	
	sprintf(strCombine, "%s%s", family_name, given_name);

	g_object_set(GTK_CELL_RENDERER(cell),
                 "text", strCombine,
                 NULL);

    #endif
}

int main(int argc, char *argv[])
{	
	gtk_init(&argc, &argv);
	
	static GtkWidget *window = NULL;
	GtkWidget *vbox, *frame, *box, *combo, *entry;
	GtkTreeModel *model;
	GtkCellRenderer *renderer;
	GtkTreePath *path;
	GtkTreeIter iter;

	if (!window)
	{
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	
		gtk_window_set_title(GTK_WINDOW (window), "Combo boxes");

		g_signal_connect (window, "destroy",
						  G_CALLBACK (gtk_widget_destroyed),
						  &window);

		gtk_container_set_border_width (GTK_CONTAINER (window), 10);

		vbox = gtk_vbox_new (FALSE, 2);
		gtk_container_add (GTK_CONTAINER (window), vbox);

        #if 1
		/* A combobox demonstrating cell renderers, separators and
		*	insensitive rows 
		*/
		frame = gtk_frame_new ("Some stock icons");
		gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);

		box = gtk_vbox_new (FALSE, 0);
		gtk_container_set_border_width (GTK_CONTAINER (box), 5);
		gtk_container_add (GTK_CONTAINER (frame), box);

		model = create_stock_icon_store ();
		combo = gtk_combo_box_new_with_model(model);
		g_object_unref (model);
		gtk_container_add (GTK_CONTAINER (box), combo);

		renderer = gtk_cell_renderer_pixbuf_new ();
		gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), renderer, FALSE);
		gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo), renderer,
										"pixbuf", PIXBUF_COL, 
										NULL);

		gtk_cell_layout_set_cell_data_func (GTK_CELL_LAYOUT (combo),
											renderer,
											set_sensitive,
											NULL, NULL);

		renderer = gtk_cell_renderer_text_new ();
		gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), renderer, TRUE);
		gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo), renderer,
										"text", TEXT_COL,
										NULL);

		gtk_cell_layout_set_cell_data_func (GTK_CELL_LAYOUT (combo),
											renderer,
											set_sensitive,
											NULL, NULL);

		gtk_combo_box_set_row_separator_func (GTK_COMBO_BOX (combo), 
			                                  is_separator, NULL, NULL);

		gtk_combo_box_set_active (GTK_COMBO_BOX (combo), 0);
        #endif

        #if 0
		/* A combobox demonstrating trees.
		*/
		frame = gtk_frame_new ("Where are we ?");
		gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);

		box = gtk_vbox_new (FALSE, 0);
		gtk_container_set_border_width (GTK_CONTAINER (box), 5);
		gtk_container_add (GTK_CONTAINER (frame), box);

		model = create_capital_store ();
		combo = gtk_combo_box_new_with_model (model);
		g_object_unref (model);
		gtk_container_add (GTK_CONTAINER (box), combo);

		renderer = gtk_cell_renderer_text_new ();
		gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), renderer, TRUE);
		gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo), renderer,
										"text", 0,
										NULL);
		gtk_cell_layout_set_cell_data_func (GTK_CELL_LAYOUT (combo),
											renderer,
											is_capital_sensitive,
											NULL, NULL);

		path = gtk_tree_path_new_from_indices (0, 8, -1);
		gtk_tree_model_get_iter (model, &iter, path);
		gtk_tree_path_free (path);
		gtk_combo_box_set_active_iter (GTK_COMBO_BOX (combo), &iter);
        #endif
	 
        #if 0
		/* A GtkComboBoxEntry with validation.
		*/
		frame = gtk_frame_new ("Editable");
		gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);

		box = gtk_vbox_new (FALSE, 0);
		gtk_container_set_border_width (GTK_CONTAINER (box), 5);
		gtk_container_add (GTK_CONTAINER (frame), box);

		combo = gtk_combo_box_entry_new_text ();
		fill_combo_entry (combo);
		gtk_container_add (GTK_CONTAINER (box), combo);

		entry = g_object_new (TYPE_MASK_ENTRY, NULL);
		MASK_ENTRY (entry)->mask = "^([0-9]*|One|Two|2\302\275|Three)$";

		gtk_container_remove (GTK_CONTAINER (combo), GTK_BIN (combo)->child);
		gtk_container_add (GTK_CONTAINER (combo), entry);
        #endif
	}

	if (!GTK_WIDGET_VISIBLE (window))
	{
		gtk_widget_show_all (window);
	}
	else
	{	 
		gtk_widget_destroy (window);
		window = NULL;
	}
	
    #if 0
	GtkWidget *window;
	GtkWidget *fix;
	GtkListStore *store;
	GtkWidget *notebook;
	GtkTreeModel *tree_model;
	GtkWidget *treeview;
	GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
	GtkWidget  *combobox;
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "combobox.glade", NULL);
	
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
	fix = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	combobox = GTK_WIDGET(gtk_builder_get_object(builder, "combobox1"));
	
	
	
	store = create_store();
	tree_model = fill_store(store);
	
	gtk_combo_box_set_model(combobox, tree_model);
	
    gtk_widget_set_size_request(combobox, 100, 30);


	renderer = gtk_cell_renderer_pixbuf_new();
    gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combobox), renderer, FALSE);
	
    gtk_cell_layout_set_cell_data_func (GTK_CELL_LAYOUT (combobox),
										renderer,
										set_sensitive,
										NULL, NULL);
   
	gtk_combo_box_set_active(GTK_COMBO_BOX (combobox), 0);
    
    gtk_builder_connect_signals(builder, notebook);
	
    gtk_widget_show_all(window);
    #endif

	gtk_main();
    
	//combobox = gtk_combo_box_new_text();
	//combobox = gtk_combo_box_new();
	
	//gtk_combo_box_append_text(GTK_COMBO_BOX(combobox), "test");
	//gtk_combo_box_append_text(GTK_COMBO_BOX(combobox), "test2");
	//gtk_combo_box_set_active(GTK_COMBO_BOX(combobox), 0);
    return 0;
}

