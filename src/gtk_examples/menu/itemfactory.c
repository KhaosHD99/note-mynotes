
#include <gtk/gtk.h>
#include <strings.h>

/* 必须的基本回调 */
static void print_hello( GtkWidget *w,
						gpointer   data )
{
	g_message ("Hello, World!\n");
}

/* 这是用来生成新菜单的 GtkItemFactoryEntry 结构。
第一项：菜单路径。下划线后的字母指出菜单打开时
的快捷键。
第二项：这个条目的快捷键
第三项：回调函数。
第四项：回调动作。这个改变被调用的函数的参数。默认是0.
第五项：项类型，用来定义它是哪种项，
这里是可能的值：

 NULL               -> "<Item>"
 ""                 -> "<Item>"
 "<Title>"          -> 创建一个标题(title)项
 "<Item>"           -> 创建一个简单(simple)项
 "<CheckItem>"      -> 创建一个检查(check)项
 "<ToggleItem>"     -> 创建一个开关(toggle)项
 "<RadioItem>"      -> 创建一个选择(radio)项
 <path>             -> 选择项连接到的路径
 "<Separator>"      -> 创建一个分隔线(separator)
 "<Branch>"         -> 创建一个包含子项的项（可选）
 "<LastBranch>"     -> 创建一个右对齐的分枝(branch)
*/

static GtkItemFactoryEntry menu_items[] = {
	{ "/_File",         NULL,         NULL, 0, "<Branch>" },
	{ "/File/_New",     "<control>N", print_hello, 0, NULL },
	{ "/File/_Open",    "<control>O", print_hello, 0, NULL },
	{ "/File/_Save",    "<control>S", print_hello, 0, NULL },
	{ "/File/Save _As", NULL,         NULL, 0, NULL },
	{ "/File/sep1",     NULL,         NULL, 0, "<Separator>" },
	{ "/File/Quit",     "<control>Q", gtk_main_quit, 0, NULL },
	{ "/_Options",      NULL,         NULL, 0, "<Branch>" },
	{ "/Options/Test",  NULL,         NULL, 0, NULL },
	{ "/_Help",         NULL,         NULL, 0, "<LastBranch>" },
	{ "/_Help/About",   NULL,         NULL, 0, NULL },
};


void get_main_menu( GtkWidget  *window,
				   GtkWidget **menubar )
{
	GtkItemFactory *item_factory;
	GtkAccelGroup *accel_group;
	gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);
	
	accel_group = gtk_accel_group_new ();
	
	/* 这个函数初始化套件。
	参数1：菜单类型 - 可以是GTK_TYPE_MENU_BAR, GTK_TYPE_MENU,
	或GTK_TYPE_OPTION_MENU。
	参数2：菜单路径。
	参数3：指向一个gtk_accel_group的指针。套件在生成菜单时设置
	好加速表(accelerator table)。
	*/
	
	item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>", 
		accel_group);
	
		/* 这个函数生成菜单项。把数组里项的数量，数组自身，和菜单项的任
	意回调数据依次传递给套件。 */
	gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);
	
	/* 把新的加速组绑定到窗口。 */
	gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);
	
	if (menubar)
		/* 最后，返回套件已经创建的菜单栏。 */ 
		*menubar = gtk_item_factory_get_widget (item_factory, "<main>");
}

int main( int argc,
		 char *argv[] )
{
	GtkWidget *window;
	GtkWidget *main_vbox;
	GtkWidget *menubar;
	
	gtk_init (&argc, &argv);
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT (window), "destroy", 
		G_CALLBACK (gtk_main_quit), 
		NULL);
	gtk_window_set_title (GTK_WINDOW (window), "Item Factory");
	gtk_widget_set_size_request (GTK_WIDGET (window), 300, 200);
	
	main_vbox = gtk_vbox_new (FALSE, 1);
	gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 1);
	gtk_container_add (GTK_CONTAINER (window), main_vbox);
	gtk_widget_show (main_vbox);
	
	get_main_menu (window, &menubar);
	gtk_box_pack_start (GTK_BOX (main_vbox), menubar, FALSE, TRUE, 0);
	gtk_widget_show (menubar);
	
	gtk_widget_show (window);
	
	gtk_main ();
	
	return 0;
}
