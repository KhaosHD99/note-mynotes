#include <gtk/gtk.h>
#define TYPE_MASK_ENTRY	(mask_entry_get_type ())
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

static void mask_entry_init (MaskEntry *entry)
{
  entry->mask = NULL;
}

static void mask_entry_class_init (MaskEntryClass *klass){}
static void mask_entry_editable_init (GtkEditableClass *iface){}

G_DEFINE_TYPE_WITH_CODE (MaskEntry, mask_entry, GTK_TYPE_ENTRY,
						 G_IMPLEMENT_INTERFACE (GTK_TYPE_EDITABLE,
					     mask_entry_editable_init));
					     
static void fill_combo_entry (GtkWidget *entry)
{
  gtk_combo_box_append_text (GTK_COMBO_BOX (entry), "One");
  gtk_combo_box_append_text (GTK_COMBO_BOX (entry), "Two");
  gtk_combo_box_append_text (GTK_COMBO_BOX (entry), "2\302\275");
  gtk_combo_box_append_text (GTK_COMBO_BOX (entry), "Three");
}

int main(int argc, char **argv)
{
	gtk_init(&argc,&argv);
	static GtkWidget *window = NULL;
	GtkWidget *frame, *box, *combo, *entry;
	if (!window)
	{
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title (GTK_WINDOW (window), "Combo boxes");

		g_signal_connect (window, "destroy", G_CALLBACK (gtk_widget_destroyed), &window);

		gtk_container_set_border_width (GTK_CONTAINER (window), 10);

		frame = gtk_frame_new ("Editable");
		gtk_container_add (GTK_CONTAINER (window), frame);

		box = gtk_vbox_new (FALSE, 0);
		gtk_container_add (GTK_CONTAINER (frame), box);

		combo = gtk_combo_box_entry_new_text ();
		fill_combo_entry (combo);
		gtk_container_add (GTK_CONTAINER (box), combo);

		entry = g_object_new (TYPE_MASK_ENTRY, NULL);
		//MASK_ENTRY (entry)->mask = "^([0-9]*|One|Two|2\302\275|Three)$";
 
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
	gtk_widget_show_all (window);
	gtk_main ();
}
