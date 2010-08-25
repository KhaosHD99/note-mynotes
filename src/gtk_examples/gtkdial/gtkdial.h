
/* GTK - GIMP���߰�
 * ��Ȩ (C) 1995-1997 Peter Mattis, Spencer Kimball �� Josh MacDonald ����
 *
 * ����������������������������������𷢲��� GNU GPL �����������·ַ�
 * ���޸�����GPL ����ʹ�ð汾 2 ��(����ѡ��)�κ����İ汾��
 *
 * ������ַ���Ŀ���������ܶ����������ã������ṩ�κεĵ���������������
 * ���ʺ��ض���;�ı�֤�������GNUͨ�ù������֤�����ϸ����Ϣ��
 *
 * ��Ӧ���Ѿ�������һ���յ�һ��GNUͨ�ù�����ɡ������û�У���д�Ÿ�
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

  /* ���·�ʽ (GTK_UPDATE_[CONTINUOUS/DELAYED/DISCONTINUOUS]) */
  guint policy : 2;

  /* ��ǰ���µİ�ť�����û�и�ֵ�� 0 */
  guint8 button;

  /* ����ָ��Ĵ�С */
  gint radius;
  gint pointer_width;

  /* ���¼�ʱ����ID , ���û�и�ֵ�� 0 */
  guint32 timer;

  /* ��ǰ�Ƕ� */
  gfloat angle;
  gfloat last_angle;

  /* ���ӵ��������еõ��ľ�ֵ���������������ڸı�ʱ���Ǿͻ�֪�� */
  gfloat old_value;
  gfloat old_lower;
  gfloat old_upper;

  /* Ϊ������̹����洢���ݵĵ������� */
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
