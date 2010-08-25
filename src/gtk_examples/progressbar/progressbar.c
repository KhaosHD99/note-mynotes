
#include <gtk/gtk.h>

typedef struct _ProgressData {
  GtkWidget *window;
  GtkWidget *pbar;
  int timer;
  gboolean activity_mode;
} ProgressData;

/* 更新进度条，这样就能够看到进度条的移动 */
gint progress_timeout( gpointer data )
{
  ProgressData *pdata = (ProgressData *)data;
  gdouble new_val;
  
  if (pdata->activity_mode) 
    gtk_progress_bar_pulse (GTK_PROGRESS_BAR (pdata->pbar));
  else 
    {
      /* 使用在调整对象中设置的取值范围计算进度条的值 */
      
      new_val = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (pdata->pbar)) + 0.01;
      
      if (new_val > 1.0)
	new_val = 0.0;
      
      /* 设置进度条的新值 */
      gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (pdata->pbar), new_val);
    }
  
  /* 这是一个timeout函数，返回 TRUE，这样它就能够继续被调用 */
  return TRUE;
} 

/* 回调函数，切换在进度条你的滑槽上的文本显示 */
void toggle_show_text( GtkWidget    *widget,
		       ProgressData *pdata )
{
  const gchar *text;
  
  text = gtk_progress_bar_get_text (GTK_PROGRESS_BAR (pdata->pbar));
  if (text && *text)
    gtk_progress_bar_set_text (GTK_PROGRESS_BAR (pdata->pbar), "");
  else 
    gtk_progress_bar_set_text (GTK_PROGRESS_BAR (pdata->pbar), "some text");
}

/* 回调函数，切换进度条的活动模式 */
void toggle_activity_mode( GtkWidget    *widget,
			   ProgressData *pdata )
{
  pdata->activity_mode = !pdata->activity_mode;
  if (pdata->activity_mode) 
      gtk_progress_bar_pulse (GTK_PROGRESS_BAR (pdata->pbar));
  else
      gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (pdata->pbar), 0.0);
}

 
/* 回调函数，切换进度条的移动方向 */
void toggle_orientation( GtkWidget    *widget,
			 ProgressData *pdata )
{
  switch (gtk_progress_bar_get_orientation (GTK_PROGRESS_BAR (pdata->pbar))) {
  case GTK_PROGRESS_LEFT_TO_RIGHT:
    gtk_progress_bar_set_orientation (GTK_PROGRESS_BAR (pdata->pbar), 
				      GTK_PROGRESS_RIGHT_TO_LEFT);
    break;
  case GTK_PROGRESS_RIGHT_TO_LEFT:
    gtk_progress_bar_set_orientation (GTK_PROGRESS_BAR (pdata->pbar), 
				      GTK_PROGRESS_LEFT_TO_RIGHT);
    break;
  default:
    // 什么也不做
  }
}

 
/* 清除分配的内存，删除定时器(timer) */
void destroy_progress( GtkWidget     *widget,
		       ProgressData *pdata)
{
    gtk_timeout_remove (pdata->timer);
    pdata->timer = 0;
    pdata->window = NULL;
    g_free (pdata);
    gtk_main_quit ();
}

int main( int   argc,
          char *argv[])
{
    ProgressData *pdata;
    GtkWidget *align;
    GtkWidget *separator;
    GtkWidget *table;
    GtkWidget *button;
    GtkWidget *check;
    GtkWidget *vbox;

    gtk_init (&argc, &argv);

    /* 为传递到回调函数中的数据分配内存 */
    pdata = g_malloc (sizeof (ProgressData));
  
    pdata->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable (GTK_WINDOW (pdata->window), TRUE);

    g_signal_connect (G_OBJECT (pdata->window), "destroy",
	              G_CALLBACK (destroy_progress),
                      pdata);
    gtk_window_set_title (GTK_WINDOW (pdata->window), "GtkProgressBar");
    gtk_container_set_border_width (GTK_CONTAINER (pdata->window), 0);

    vbox = gtk_vbox_new (FALSE, 5);
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);
    gtk_container_add (GTK_CONTAINER (pdata->window), vbox);
    gtk_widget_show (vbox);
  
    /* 创建一个居中对齐的对象 */
    align = gtk_alignment_new (0.5, 0.5, 0, 0);
    gtk_box_pack_start (GTK_BOX (vbox), align, FALSE, FALSE, 5);
    gtk_widget_show (align);

    /* 创建进度条 */
    pdata->pbar = gtk_progress_bar_new ();

    gtk_container_add (GTK_CONTAINER (align), pdata->pbar);
    gtk_widget_show (pdata->pbar);

    /* 加一个定时器(timer)，以更新进度条的值 */
    pdata->timer = gtk_timeout_add (100, progress_timeout, pdata);

    separator = gtk_hseparator_new ();
    gtk_box_pack_start (GTK_BOX (vbox), separator, FALSE, FALSE, 0);
    gtk_widget_show (separator);

    /* 行数、列数、同质性(homogeneous) */
    table = gtk_table_new (2, 2, FALSE);
    gtk_box_pack_start (GTK_BOX (vbox), table, FALSE, TRUE, 0);
    gtk_widget_show (table);

    /* 添加一个复选按钮，以选择是否显示在滑槽里的文本 */
    check = gtk_check_button_new_with_label ("Show text");
    gtk_table_attach (GTK_TABLE (table), check, 0, 1, 0, 1,
                      GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL,
		      5, 5);
    g_signal_connect (G_OBJECT (check), "clicked",
                      G_CALLBACK (toggle_show_text),
                      pdata);
    gtk_widget_show (check);

    /* 添加一个复选按钮，切换活动状态 */
    check = gtk_check_button_new_with_label ("Activity mode");
    gtk_table_attach (GTK_TABLE (table), check, 0, 1, 1, 2,
                      GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL,
                      5, 5);
    g_signal_connect (G_OBJECT (check), "clicked",
                      G_CALLBACK (toggle_activity_mode),
                      pdata);
    gtk_widget_show (check);

    /* 添加一个复选按钮，切换移动方向 */
    check = gtk_check_button_new_with_label ("Right to Left");
    gtk_table_attach (GTK_TABLE (table), check, 0, 1, 2, 3,
                      GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL,
                      5, 5);
    g_signal_connect (G_OBJECT (check), "clicked",
                      G_CALLBACK (toggle_orientation),
                      pdata);
    gtk_widget_show (check);

    /* 添加一个按钮，用来退出应用程序 */
    button = gtk_button_new_with_label ("close");
    g_signal_connect_swapped (G_OBJECT (button), "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                              pdata->window);
    gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

    /* 将按钮设置为能缺省的构件 */
    GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);

    /* 将缺省焦点设置到这个按钮上，使之成为缺省按钮，只要按回车键
     * 就相当于点击了这个按钮 */
       //译者注： 能缺省的构件在获取焦点后成为缺省构件,用户按方向键等可以切换焦点。
    gtk_widget_grab_default (button);
    gtk_widget_show (button);

    gtk_widget_show (pdata->window);

    gtk_main ();
    
    return 0;
}
