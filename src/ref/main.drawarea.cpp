#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//xorg
#include <X11/Xlib.h>
#include <X11/Xutil.h>

//gtk


#include <cairo.h>
#include <gtk/gtk.h>


const int BUFSIZE = 32 * 1024;
const int window_width = 800;
const int window_height = 480;
int run_state = 0;

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *label;
void gtk_win_destroy(GtkWidget *widget,gpointer data)
{
	printf("recv gtk_win_destroy \n");
	run_state = 1;
    gtk_main_quit();
}
static void *v4l_show(void* lpParameter)
{

	int x = 0;
	int y = 0;
	while(1)
	{
		sleep(1);
		x+=15;
		y+=15;
		gtk_fixed_move (GTK_FIXED (fixed),
										label,
										x,
										y); 
		printf("move label[%d:%d]\r\n", x, y);
	}
}

gint RepaintClock (gpointer data)
{
	static int x = 0;
	static int y = 0;

	x+=15;
	y+=15;

	gtk_fixed_move (GTK_FIXED (fixed),
									label,
									x,
									y); 
	printf("move label[%d:%d]\r\n", x, y);

   return (TRUE);
}
struct _Ourarg {
	gint right;
	gint left;
};

void *thread_go(struct _Ourarg *arg)
{
	static int x = 0;
	static int y = 0;
	gint sleep_val = 1000;
	for(;;)
	{
		x+=15;
		y+=15;
		g_usleep(sleep_val);

		gdk_threads_enter();
		gtk_fixed_move (GTK_FIXED (fixed),
								label,
								x,
								y); 
		printf("move label[%d:%d]\r\n", x, y);

		gdk_threads_leave();		
	}	
}

int main(int argc, char *argv[])
{
	pthread_t v4l_thread;
	struct _Ourarg ourarg;


	if(XInitThreads () == 0)
		printf(" XInitThreads err\n");

	if(!g_thread_supported()) g_thread_init(NULL);
	gdk_threads_init();
	  
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
///////////////////////////////////////////////////////
	fixed = gtk_fixed_new ();
	gtk_container_add(GTK_CONTAINER(window),fixed);
	gtk_widget_show(fixed);
      
	label = gtk_label_new ("123456789012345678901234567890");
	gtk_container_add (GTK_CONTAINER (fixed), label);
	gtk_fixed_move (GTK_FIXED (fixed), label, 0, 10); 
	gtk_widget_show(label);

    gtk_fixed_move (GTK_FIXED (fixed),
                                    label,
                                    200,
                                    0); 

    gtk_window_set_resizable(GTK_WINDOW(window),TRUE);
    gtk_window_resize(GTK_WINDOW(window), window_width,window_height);

	gtk_widget_show(window);
	 
/*
	if( pthread_create(&v4l_thread, NULL, v4l_show, NULL) == 0)
		printf("thread create Ok, v4l show thread start \n");
	else
		printf("thread create Err\n");
*/
//	gtk_timeout_add (1000, RepaintClock, (gpointer) label);

	g_thread_create(thread_go, &ourarg, FALSE, NULL);
	gdk_threads_enter();
	gtk_main();
	gdk_threads_leave();


	printf("gtk main end \n");

	return 0;
}
