
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

#include <gtk/gtk.h>

/* 绘制区的后端位图 */
static GdkPixmap *pixmap = NULL;

/* 创建一个适当大小的后端位图 */
static gint
configure_event (GtkWidget *widget, GdkEventConfigure *event)
{
  if (pixmap)
     g_object_unref (pixmap);

  pixmap = gdk_pixmap_new (widget->window,
                           widget->allocation.width,
                           widget->allocation.height,
                           -1);
  gdk_draw_rectangle (pixmap,
                      widget->style->white_gc,
                      TRUE,
                      0, 0,
                      widget->allocation.width,
                      widget->allocation.height);

  return TRUE;
}

/* 从后端位图重新绘制屏幕 */
static gint
expose_event (GtkWidget *widget, GdkEventExpose *event)
{
  gdk_draw_drawable (widget->window,
                     widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                     pixmap,
                     event->area.x, event->area.y,
                     event->area.x, event->area.y,
                     event->area.width, event->area.height);

  return FALSE;
}

/* 在屏幕上画一个矩形，大小依据压力，颜色依据设备的类型 */
static void
draw_brush (GtkWidget *widget, GdkInputSource source,
            gdouble x, gdouble y, gdouble pressure)
{
  GdkGC *gc;
  GdkRectangle update_rect;

  switch (source)
    {
    case GDK_SOURCE_MOUSE:
      gc = widget->style->dark_gc[GTK_WIDGET_STATE (widget)];
      break;
    case GDK_SOURCE_PEN:
      gc = widget->style->black_gc;
      break;
    case GDK_SOURCE_ERASER:
      gc = widget->style->white_gc;
      break;
    default:
      gc = widget->style->light_gc[GTK_WIDGET_STATE (widget)];
    }

  update_rect.x = x - 10 * pressure;
  update_rect.y = y - 10 * pressure;
  update_rect.width = 20 * pressure;
  update_rect.height = 20 * pressure;
  gdk_draw_rectangle (pixmap, gc, TRUE,
                      update_rect.x, update_rect.y,
                      update_rect.width, update_rect.height);
  gtk_widget_queue_draw_area (widget, 
                      update_rect.x, update_rect.y,
                      update_rect.width, update_rect.height);
}

static void
print_button_press (GdkDevice *device)
{
  g_print ("Button press on device '%s'\n", device->name);
}

static gint
button_press_event (GtkWidget *widget, GdkEventButton *event)
{
  print_button_press (event->device);
  
  if (event->button == 1 && pixmap != NULL) {
    gdouble pressure;
    gdk_event_get_axis ((GdkEvent *)event, GDK_AXIS_PRESSURE, &pressure);
    draw_brush (widget, event->device->source, event->x, event->y, pressure);
  }

  return TRUE;
}

static gint
motion_notify_event (GtkWidget *widget, GdkEventMotion *event)
{
  gdouble x, y;
  gdouble pressure;
  GdkModifierType state;

  if (event->is_hint) 
    {
      gdk_device_get_state (event->device, event->window, NULL, &state);
      gdk_event_get_axis ((GdkEvent *)event, GDK_AXIS_X, &x);
      gdk_event_get_axis ((GdkEvent *)event, GDK_AXIS_Y, &y);
      gdk_event_get_axis ((GdkEvent *)event, GDK_AXIS_PRESSURE, &pressure);
    }
  else
    {
      x = event->x;
      y = event->y;
      gdk_event_get_axis ((GdkEvent *)event, GDK_AXIS_PRESSURE, &pressure);
      state = event->state;
    }
    
  if (state & GDK_BUTTON1_MASK && pixmap != NULL)
    draw_brush (widget, event->device->source, x, y, pressure);
  
  return TRUE;
}

void
input_dialog_destroy (GtkWidget *w, gpointer data)
{
  *((GtkWidget **)data) = NULL;
}

void
create_input_dialog ()
{
  static GtkWidget *inputd = NULL;

  if (!inputd)
    {
      inputd = gtk_input_dialog_new();

      g_signal_connect (G_OBJECT (inputd), "destroy",
                        G_CALLBACK (input_dialog_destroy), &inputd);
      g_signal_connect_swapped (G_OBJECT (GTK_INPUT_DIALOG (inputd)->close_button),
                                "clicked",
                                G_CALLBACK (gtk_widget_hide),
                                inputd);
      gtk_widget_hide (GTK_INPUT_DIALOG (inputd)->save_button);

      gtk_widget_show (inputd);
    }
  else
    {
      if (!GTK_WIDGET_MAPPED (inputd))
        gtk_widget_show (inputd);
      else
        gdk_window_raise (inputd->window);
    }
}

void
quit ()
{
  exit (0);
}

int
main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *drawing_area;
  GtkWidget *vbox;

  GtkWidget *button;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (window, "Test Input");

  vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show (vbox);

  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (quit), NULL);

  /* 创建绘图区 */

  drawing_area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (GTK_WIDGET (drawing_area), 200, 200);
  gtk_box_pack_start (GTK_BOX (vbox), drawing_area, TRUE, TRUE, 0);

  gtk_widget_show (drawing_area);

  /* 用于处理后端位图的信号 */

  g_signal_connect (G_OBJECT (drawing_area), "expose_event",
                    G_CALLBACK (expose_event), NULL);
  g_signal_connect (G_OBJECT(drawing_area),"configure_event",
                    G_CALLBACK (configure_event), NULL);

  /* 事件信号 */

  g_signal_connect (G_OBJECT (drawing_area), "motion_notify_event",
                    G_CALLBACK (motion_notify_event), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "button_press_event",
                    G_CALLBACK (button_press_event), NULL);

  gtk_widget_set_events (drawing_area, GDK_EXPOSURE_MASK
                         | GDK_LEAVE_NOTIFY_MASK
                         | GDK_BUTTON_PRESS_MASK
                         | GDK_POINTER_MOTION_MASK
                         | GDK_POINTER_MOTION_HINT_MASK);

  /* 下面的调用允许为绘图区跟踪和处理扩展事件 */
  gtk_widget_set_extension_events (drawing_area, GDK_EXTENSION_EVENTS_CURSOR);

  /* 几个按钮 */
  button = gtk_button_new_with_label ("Input Dialog");
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

  g_signal_connect (G_OBJECT (button), "clicked",
                    G_CALLBACK (create_input_dialog), NULL);
  gtk_widget_show (button);

  button = gtk_button_new_with_label ("Quit");
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

  g_signal_connect_swapped (G_OBJECT (button), "clicked",
                            G_CALLBACK (gtk_widget_destroy),
                            window);
  gtk_widget_show (button);

  gtk_widget_show (window);

  gtk_main ();

  return 0;
}
