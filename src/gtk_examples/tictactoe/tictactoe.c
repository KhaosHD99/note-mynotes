
/* GTK - GIMP工具包
 * 版权 (C) 1995-1997 Peter Mattis, Spencer Kimball 和 Josh MacDonald 所有
 *
 * 本程序是自由软件。你可以在自由软件基金发布的 GNU GPL 的条款下重新分发
 * 或修改它。GPL 可以使用版本 2 或(由你选择)任何随后的版本。
 *
 * 本程序分发的目的是它可能对其他人有用，但不提供任何的担保，包括隐含的
 * 和适合特定用途的保证。请查阅GNU通用公共许可证获得详细的信息。
 *
 * 你应该已经随该软件一起收到一份GNU通用公共许可。如果还没有，请写信给
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "gtk/gtksignal.h"
#include "gtk/gtktable.h"
#include "gtk/gtktogglebutton.h"
#include "tictactoe.h"

enum {
  TICTACTOE_SIGNAL,
  LAST_SIGNAL
};

static void tictactoe_class_init          (TictactoeClass *klass);
static void tictactoe_init                (Tictactoe      *ttt);
static void tictactoe_toggle              (GtkWidget *widget, Tictactoe *ttt);

static gint tictactoe_signals[LAST_SIGNAL] = { 0 };

GType
tictactoe_get_type ()
{
  static GType ttt_type = 0;

  if (!ttt_type)
    {
      static const GTypeInfo ttt_info =
      {
	sizeof (TictactoeClass),
	NULL,
        NULL,
	(GClassInitFunc) tictactoe_class_init,
        NULL,
	NULL,
        sizeof (Tictactoe),
	0,
	(GInstanceInitFunc) tictactoe_init,
      };

      ttt_type = g_type_register_static (GTK_TYPE_VBOX, "Tictactoe", &ttt_info, 0);
    }

  return ttt_type;
}

static void
tictactoe_class_init (TictactoeClass *class)
{
  GtkObjectClass *object_class;

  object_class = (GtkObjectClass*) class;
  
  tictactoe_signals[TICTACTOE_SIGNAL] = g_signal_new ("tictactoe",
					 G_TYPE_FROM_CLASS (object_class),
	                                 G_SIGNAL_RUN_FIRST,
	                                 0,
                                         NULL, 
                                         NULL,                
					 g_cclosure_marshal_VOID__VOID,
                                         G_TYPE_NONE, 0, NULL);


  class->tictactoe = NULL;
}

static void
tictactoe_init (Tictactoe *ttt)
{
  GtkWidget *table;
  gint i,j;
  
  table = gtk_table_new (3, 3, TRUE);
  gtk_container_add (GTK_CONTAINER (ttt), table);
  gtk_widget_show (table);

  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      {
	ttt->buttons[i][j] = gtk_toggle_button_new ();
	gtk_table_attach_defaults (GTK_TABLE (table), ttt->buttons[i][j], 
				   i, i+1, j, j+1);
	g_signal_connect (G_OBJECT (ttt->buttons[i][j]), "toggled",
			  G_CALLBACK (tictactoe_toggle), ttt);
	gtk_widget_set_size_request (ttt->buttons[i][j], 20, 20);
	gtk_widget_show (ttt->buttons[i][j]);
      }
}

GtkWidget*
tictactoe_new ()
{
  return GTK_WIDGET (g_object_new (tictactoe_get_type (), NULL));
}

void	       
tictactoe_clear (Tictactoe *ttt)
{
  int i,j;

  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      {
	g_signal_handlers_block_by_func (G_OBJECT (ttt->buttons[i][j]), 
                                         NULL, ttt);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (ttt->buttons[i][j]),
				      FALSE);
	g_signal_handlers_unblock_by_func (G_OBJECT (ttt->buttons[i][j]), 
                                           NULL, ttt);
      }
}

static void
tictactoe_toggle (GtkWidget *widget, Tictactoe *ttt)
{
  int i,k;

  static int rwins[8][3] = { { 0, 0, 0 }, { 1, 1, 1 }, { 2, 2, 2 },
			     { 0, 1, 2 }, { 0, 1, 2 }, { 0, 1, 2 },
			     { 0, 1, 2 }, { 0, 1, 2 } };
  static int cwins[8][3] = { { 0, 1, 2 }, { 0, 1, 2 }, { 0, 1, 2 },
			     { 0, 0, 0 }, { 1, 1, 1 }, { 2, 2, 2 },
			     { 0, 1, 2 }, { 2, 1, 0 } };

  int success, found;

  for (k = 0; k < 8; k++)
    {
      success = TRUE;
      found = FALSE;

      for (i = 0; i < 3; i++)
	{
	  success = success && 
	    GTK_TOGGLE_BUTTON (ttt->buttons[rwins[k][i]][cwins[k][i]])->active;
	  found = found ||
	    ttt->buttons[rwins[k][i]][cwins[k][i]] == widget;
	}
      
      if (success && found)
	{
	  g_signal_emit (G_OBJECT (ttt), 
	                 tictactoe_signals[TICTACTOE_SIGNAL], 0);
	  break;
	}
    }
}

