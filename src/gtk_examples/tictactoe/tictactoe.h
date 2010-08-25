
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

#ifndef __TICTACTOE_H__
#define __TICTACTOE_H__


#include <gdk/gdk.h>
#include <gtk/gtkvbox.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TICTACTOE(obj)          GTK_CHECK_CAST (obj, tictactoe_get_type (), Tictactoe)
#define TICTACTOE_CLASS(klass)  GTK_CHECK_CLASS_CAST (klass, tictactoe_get_type (), TictactoeClass)
#define IS_TICTACTOE(obj)       GTK_CHECK_TYPE (obj, tictactoe_get_type ())


typedef struct _Tictactoe       Tictactoe;
typedef struct _TictactoeClass  TictactoeClass;

struct _Tictactoe
{
  GtkVBox vbox;
  
  GtkWidget *buttons[3][3];
};

struct _TictactoeClass
{
  GtkVBoxClass parent_class;

  void (* tictactoe) (Tictactoe *ttt);
};

GtkType        tictactoe_get_type        (void);
GtkWidget*     tictactoe_new             (void);
void	       tictactoe_clear           (Tictactoe *ttt);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TICTACTOE_H__ */

