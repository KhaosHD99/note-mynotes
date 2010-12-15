/////////////////////////////////////////////////////////////////////////////////////////////////
static int ismapped(Display *display, Window client)
{
	XWindowAttributes attr;
	int rval = 0;


	if (XGetWindowAttributes(display, client, &attr))
		rval = attr.map_state != IsUnmapped;

	return rval;
}

static void remap(Display *display, Window win)
{
	if(display != NULL)
	{
		//XUnmapWindow(display,win);
		XMapRaised(display,win);
		XFlush(display);
		//XMapWindow(display, win);
		//XFlush(display);
	}
	printf("remap on window_id : %d\r\n", win);
}

static void unmap(Display *display, Window win)
{
	if(display != NULL)
	{
		XUnmapWindow(display,win);
	}
	printf("unmap on window_id : %d\r\n", win);
}

int gtk_ismapped(GtkWidget *window)
{
	if(window)
	{
		//取得窗口相关的X11 Display
		//Display *display;

		Window xWindow = GDK_WINDOW_XID(window->window);

		if ( g_display == NULL )
		{
			printf("Cannot connect to X server \n");
			return -1;
		}
		else
		{
			//printf("connect to Xserver on XWindow %d\r\n", xWindow);
			return ismapped(g_display , xWindow);
		}
	}
	printf("%s : widget null\r\n", __FUNCTION__);
	return -1;
}

int gtk_remap(GtkWidget *window)
{
	if(window)
	{
		//取得窗口相关的X11 Display
		//Display *display;

		Window xWindow = GDK_WINDOW_XID(window->window);

		if ( g_display == NULL )
		{
			printf("Cannot connect to X server \n");
			return -1;
		}
		else
		{
			//printf("connect to Xserver on XWindow %d\r\n", xWindow);
			remap(g_display , xWindow);
			return 0;
		}
	}
	printf("%s : widget null\r\n", __FUNCTION__);
	return -1;
}

int gtk_unmap(GtkWidget *window)
{
	if(window)
	{
		//取得窗口相关的X11 Display
		//Display *display;

		Window xWindow = GDK_WINDOW_XID(window->window);

		if ( g_display == NULL )
		{
			printf("Cannot connect to X server \n");
			return -1;
		}
		else
		{
			//printf("connect to Xserver on XWindow %d\r\n", xWindow);
			unmap(g_display , xWindow);
			return 0;
		}
	}
	printf("%s : widget null\r\n", __FUNCTION__);
	return -1;
}
/////////////////////////////////////////////////////////////////////
