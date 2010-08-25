
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

#ifndef __GTK_DIAL_H__
#define __GTK_DIAL_H__


#include <gdk/gdk.h>
#include <gtk/gtkadjustment.h>
#include <gtk/gtkwidget.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define GTK_DIAL(obj)          GTK_CHECK_CAST (obj, gtk_dial_get_type (), GtkDial)
#define GTK_DIAL_CLASS(klass)  GTK_CHECK_CLASS_CAST (klass, gtk_dial_get_type (), GtkDialClass)
#define GTK_IS_DIAL(obj)       GTK_CHECK_TYPE (obj, gtk_dial_get_type ())


typedef struct _GtkDial        GtkDial;
typedef struct _GtkDialClass   GtkDialClass;

struct _GtkDial
{
  GtkWidget widget;

  /* 更新方式 (GTK_UPDATE_[CONTINUOUS/DELAYED/DISCONTINUOUS]) */
  guint policy : 2;

  /* 当前按下的按钮，如果没有该值是 0 */
  guint8 button;

  /* 表盘指针的大小 */
  gint radius;
  gint pointer_width;

  /* 更新计时器的ID , 如果没有该值是 0 */
  guint32 timer;

  /* 当前角度 */
  gfloat angle;
  gfloat last_angle;

  /* 将从调整对象中得到的旧值保存起来，这样在改变时我们就会知道 */
  gfloat old_value;
  gfloat old_lower;
  gfloat old_upper;

  /* 为这个表盘构件存储数据的调整对象 */
  GtkAdjustment *adjustment;
};

struct _GtkDialClass
{
  GtkWidgetClass parent_class;
};


GtkWidget*     gtk_dial_new                    (GtkAdjustment *adjustment);
GtkType        gtk_dial_get_type               (void);
GtkAdjustment* gtk_dial_get_adjustment         (GtkDial      *dial);
void           gtk_dial_set_update_policy      (GtkDial      *dial,
						GtkUpdateType  policy);

void           gtk_dial_set_adjustment         (GtkDial      *dial,
						GtkAdjustment *adjustment);
#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GTK_DIAL_H__ */
