#include <gtk/gtk.h>
#include <webkit/webkit.h>

static GtkWidget* main_window;
static GtkWidget* uri_entry;
static GtkStatusbar* main_statusbar;
static WebKitWebView* web_view;
static WebKitWebView* web_view2;
static GtkToolItem* button_stop;

static gchar* main_title;
static gint load_progress;
static guint status_context_id; 

static void navigation_requested_cb(GtkWidget* widget, gpointer data)
{
    printf("on [%s]\n", __FUNCTION__);
	const char* uri = webkit_web_frame_get_uri(web_view2);
    printf("[%s] uri: %s\n", __FUNCTION__, uri); 
}

static void print_requested_cb (GtkWidget* widget, gpointer data)
{
    printf("on [%s]\n", __FUNCTION__);
	const char* uri = webkit_web_view_get_uri(web_view);
    printf("[%s] uri: %s\n", __FUNCTION__, uri); 
}

static void create_gtk_window_around_it (GtkWidget* widget, gpointer data)
{
	printf("on [%s]\n", __FUNCTION__);
}

static void show_inpector_window (GtkWidget* widget, gpointer data)
{
	printf("on [%s]\n", __FUNCTION__);
}

static void inspected_uri_changed_do_stuff (GtkWidget* widget, gpointer data)
{
	printf("on [%s]\n", __FUNCTION__);
}

static load_started_cb(WebKitWebView* web_view)
{
	//const gchar* org_uri = webkit_web_navigation_action_get_original_uri(web_view2);
	//printf("[%s] org_uri: %s\n", __FUNCTION__, org_uri);

    //const gchar* target = webkit_web_navigation_action_get_target_frame(web_view2);
	//printf("[%s] target: %s\n", __FUNCTION__, target);


    WebKitWebInspector *inspector = webkit_web_view_get_inspector (WEBKIT_WEB_VIEW(web_view));
	gchar* inspector_uri;
    g_object_get (inspector,
               "inspected-uri", &inspector_uri,
               NULL);
    printf("[%s] inspected uri: %s\n", __FUNCTION__, inspector_uri);
	
    const char* uri = webkit_web_view_get_uri(web_view2);
    printf("[%s] uri: %s\n", __FUNCTION__, uri); 
   
    return TRUE;
}

static load_finished_cb(WebKitWebView* web_view)
{
    //const gchar* org_uri = webkit_web_navigation_action_get_original_uri(web_view2);
	//printf("[%s] org_uri: %s\n", __FUNCTION__, org_uri);

    //const gchar* target = webkit_web_navigation_action_get_target_frame(web_view2);
	//printf("[%s] target: %s\n", __FUNCTION__, target);

	WebKitWebInspector *inspector = webkit_web_view_get_inspector (WEBKIT_WEB_VIEW(web_view));
    gchar* inspector_uri;
    g_object_get (inspector,
               "inspected-uri", &inspector_uri,
               NULL);
    printf("[%s] inspected uri: %s\n", __FUNCTION__, inspector_uri);

    const char* uri = webkit_web_view_get_uri (web_view2);
    printf("[%s] uri: %s\n", __FUNCTION__, uri);

    return TRUE;
}

static onload_event_cb(WebKitWebView* web_view)
{
    const char* uri = webkit_web_view_get_uri (web_view);
    printf("[%s] uri: %s\n", __FUNCTION__, uri);

    return TRUE;
}

static web_view_ready_cb(WebKitWebView* web_view)
{
    const char* uri = webkit_web_view_get_uri (web_view);
    printf("[%s] uri: %s\n", __FUNCTION__, uri);

    return TRUE;
}

static gboolean show_web_view_cb (WebKitWebView* web_view)
{
    //const gchar* org_uri = webkit_web_navigation_action_get_original_uri(web_view2);
	//printf("[%s] org_uri: %s\n", __FUNCTION__, org_uri);

	const gchar* target = webkit_web_navigation_action_get_target_frame(web_view2);
	printf("[%s] target: %s\n", __FUNCTION__, target);

    //const char* uri = webkit_web_view_get_uri (web_view2);
    //printf("uri: %s\n", uri);
	WebKitWebInspector *inspector = webkit_web_view_get_inspector (WEBKIT_WEB_VIEW(web_view));

    gchar* inspector_uri;
    g_object_get (inspector,
               "inspected-uri", &inspector_uri,
               NULL);
    printf("[%s] inspected uri: %s\n", __FUNCTION__, inspector_uri);

    const char* uri = webkit_web_view_get_uri (web_view2);
    printf("[%s] uri: %s\n", __FUNCTION__, uri);

    GtkWidget* window = gtk_widget_get_toplevel(GTK_WIDGET(web_view));
    gtk_widget_show_all(window);
   
    //const char* uri = webkit_web_view_get_uri (web_view2);
    //printf("uri: %s\n", uri

    //gchar* uri;
    //g_object_get (web_view2,
    //           "uri", &uri,
    //           NULL);
    //printf("uri: %s\n", uri);

    //const gchar* req;
    //req = webkit_network_request_get_uri(web_view2);
    //printf("req: %s\n", req);

    return TRUE;
} 

static WebKitWebView* create_web_view_cb (WebKitWebView* web_view, WebKitWebFrame* web_frame)
{
	printf("on [%s] \r\n", __FUNCTION__);
#if 1
    GtkWidget* new_window;
    GtkWidget* scrolled_window;
    WebKitWebView* new_web_view = webkit_web_view_new(); 

    web_view2 = webkit_web_view_new();

    //g_signal_connect (G_OBJECT (new_web_view), "web-view-ready", G_CALLBACK (show_web_view_cb), NULL); 
    g_signal_connect (G_OBJECT (web_view2), "web-view-ready", G_CALLBACK (show_web_view_cb), NULL);
    g_signal_connect (G_OBJECT (web_view2), "load-started", G_CALLBACK (load_started_cb), NULL);
    g_signal_connect (G_OBJECT (web_view2), "load-finished", G_CALLBACK (load_finished_cb), NULL);
	g_signal_connect (G_OBJECT (web_view2), "print-requested", G_CALLBACK (print_requested_cb), NULL);
	g_signal_connect (G_OBJECT (web_view2), "navigation-requested", G_CALLBACK (navigation_requested_cb), NULL);
	

	WebKitWebInspector *inspector = webkit_web_view_get_inspector (WEBKIT_WEB_VIEW(web_view));
	
	gchar* inspector_uri;
    g_object_get (inspector,
               "inspected-uri", &inspector_uri,
               NULL);
    printf("[%s] inspected uri: %s\n", __FUNCTION__, inspector_uri);

	g_signal_connect (G_OBJECT (inspector), "inspect-web-view", G_CALLBACK(create_gtk_window_around_it), NULL);
	g_signal_connect (G_OBJECT (inspector), "show-window", G_CALLBACK(show_inpector_window), NULL);
	g_signal_connect (G_OBJECT (inspector), "notify::inspected-uri", G_CALLBACK(inspected_uri_changed_do_stuff), NULL);

    const gchar* target = webkit_web_navigation_action_get_target_frame(web_view2);
	printf("[%s] target: %s\n", __FUNCTION__, target);

	
	//const gchar* org_uri = webkit_web_navigation_action_get_original_uri(web_view2);
	//printf("[%s] org_uri: %s\n", __FUNCTION__, org_uri);
	
    new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (new_window, 380, 380); 
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
     gtk_widget_show(scrolled_window);
    //gtk_container_add(GTK_CONTAINER(new_window), scrolled_window);
    // gtk_container_add(GTK_CONTAINER(scrolled_window), new_web_view); 
    // gtk_container_add(GTK_CONTAINER(new_window), GTK_WIDGET(new_web_view));	
    gtk_container_add(GTK_CONTAINER(new_window), GTK_WIDGET(web_view2));   
    // const char* uri = webkit_web_view_get_uri (new_web_view);
    // printf("uri: %s\n", uri);
    
    //const gchar* req;
    //req = webkit_network_request_get_uri(web_view2);
    //printf("req: %s\n", req);
    
    return WEBKIT_WEB_VIEW(web_view2);    
    // return WEBKIT_WEB_VIEW(new_web_view);
    //	return new_window;
#endif
} 

static void activate_uri_entry_cb (GtkWidget* entry, gpointer data)
{
    #if 1
    printf("on [%s] \r\n", __FUNCTION__);
    const gchar* uri = gtk_entry_get_text (GTK_ENTRY (entry));
    g_assert (uri);
    webkit_web_view_open (web_view, uri);
    #endif
} 

static void update_title (GtkWindow* window)
{
    #if 1
    GString* string = g_string_new (main_title);
    g_string_append (string, " - WebKit Launcher");
    if (load_progress < 100)
        g_string_append_printf (string, " (%d%%)", load_progress);
    gchar* title = g_string_free (string, FALSE);
    gtk_window_set_title (window, title);
    g_free (title);
    #endif
} 

static void link_hover_cb (WebKitWebView* page, const gchar* title, const gchar* link, gpointer data)
{
    #if 1
	//printf("on [%s] \r\n", __FUNCTION__);
    /* underflow is allowed */
    gtk_statusbar_pop (main_statusbar, status_context_id);
    if (link)
        gtk_statusbar_push (main_statusbar, status_context_id, link);
    #endif
} 

static void title_change_cb (WebKitWebView* web_view, WebKitWebFrame* web_frame, const gchar* title, gpointer data)
{
    #if 1
	//printf("on [%s] \r\n", __FUNCTION__);
    if (main_title)
        g_free (main_title);
    main_title = g_strdup (title);
    update_title (GTK_WINDOW (main_window));
    #endif
} 

static void progress_change_cb (WebKitWebView* page, gint progress, gpointer data)
{
    #if 1
	//printf("on [%s] \r\n", __FUNCTION__);
    load_progress = progress;
    update_title (GTK_WINDOW (main_window));
    #endif
} 

static void load_commit_cb (WebKitWebView* page, WebKitWebFrame* frame, gpointer data)
{
    #if 1
	//printf("on [%s] \r\n", __FUNCTION__);
    //const char* uri_test = webkit_web_view_get_uri (web_view2);
    //printf("uri: %s\n", uri_test); 

    const gchar* uri = webkit_web_frame_get_uri(frame);
    if (uri)
        gtk_entry_set_text (GTK_ENTRY (uri_entry), uri);
    #endif
} 

static void destroy_cb (GtkWidget* widget, gpointer data)
{
    gtk_main_quit ();
} 

static void go_back_cb (GtkWidget* widget, gpointer data)
{
    #if 1
    int x, y;
    GdkScreen *screen = NULL;
	GdkDisplay *display = NULL;
	GtkWidget *widget_focus = NULL;
	GtkAllocation allocation;

	memset(&allocation , 0, sizeof(GtkAllocation));

	//gdk_screen_get_default
	display = gdk_display_get_default();
	screen = gdk_display_get_default_screen(display);

	widget_focus = gtk_window_get_focus(web_view);
	//widget_focus = gtk_container_get_focus_child (web_view);
	if(!widget_focus)
	{
		printf("[%s] widget_focus is NULL\n", __FUNCTION__);
		return;
	}
	//widget_focus->allocation.x
	//printf("on [%d] \r\n", widget_focus->allocation.x);
	//printf("on [%d] \r\n", GTK_WIDGET(button_stop)->allocation.x);
	
	//gtk_widget_get_allocation(button_stop, &allocation);
	gtk_widget_get_allocation(widget_focus, &allocation);
	//gtk_widget_get_pointer(widget_focus, &x, &y);
    printf("[%s] x: %d, y: %d, width: %d, heigh: %d\n", 
										  __FUNCTION__, 
	                                      allocation.x, 
	                                      allocation.y,
	                                      allocation.width,
	                                      allocation.height);
    #endif

    
	webkit_web_view_set_full_content_zoom(web_view, true);
	//webkit_web_view_move_cursor(web_view, 3, 1);
	
	//webkit_web_view_stop_loading(web_view2);
    //gdk_display_warp_pointer(display, screen, x, y);

	//printf("on [%s] \r\n", __FUNCTION__);
    //webkit_web_view_go_back (web_view);
} 

static void go_forward_cb (GtkWidget* widget, gpointer data)
{
    //const char* uri = webkit_web_view_get_uri (web_view2);
    //printf("uri: %s\n", uri);
    
    // const gchar* req;
    //req = webkit_network_request_get_uri(web_view);
    //printf("req: %s\n", req);



    gchar* uri;
    g_object_get (web_view2,
               "uri", &uri,
               NULL);
    printf("uri: %s\n", uri);

    const char* uri2 = webkit_web_view_get_uri (web_view);
    printf("uri_main: %s\n", uri2);
	//printf("on [%s] \r\n", __FUNCTION__);
    webkit_web_view_go_forward (web_view);
} 



/************************************************************************
start test by wyq 
*************************************************************************/
#if 0
static gboolean new_window_policy(WebKitWebView             *web_view,
                          WebKitWebFrame            *frame,
                          WebKitNetworkRequest      *request,
                          WebKitWebNavigationAction *navigation_action,
                          WebKitWebPolicyDecision   *policy_decision,
                          gpointer                   user_data) 
{
		printf("on [%s] \r\n", __FUNCTION__);
		return FALSE;
}
#endif

/************************************************************************
end test by wyq 
*************************************************************************/
static GtkWidget* create_browser ()
{	
    GtkWidget* scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC); 

    web_view = WEBKIT_WEB_VIEW (webkit_web_view_new ());
    gtk_container_add (GTK_CONTAINER (scrolled_window), GTK_WIDGET (web_view)); 

   
    //g_signal_connect (G_OBJECT (web_view), "navigation-requested", G_CALLBACK (navigation_requested_cb), NULL);
    g_signal_connect (G_OBJECT (web_view), "create-web-view", G_CALLBACK (create_web_view_cb), NULL);
    //g_signal_connect (G_OBJECT (web_view), "onload-event", G_CALLBACK (onload_event_cb), NULL);
    //g_signal_connect (G_OBJECT (web_view), "load-started", G_CALLBACK (load_started_cb), NULL);
    //g_signal_connect (G_OBJECT (web_view), "load-finished", G_CALLBACK (load_finished_cb), NULL);
    //g_signal_connect (G_OBJECT (web_view), "web-view-ready", G_CALLBACK (web_view_ready_cb), NULL);
    g_signal_connect (G_OBJECT (web_view), "title-changed", G_CALLBACK (title_change_cb), web_view);
    g_signal_connect (G_OBJECT (web_view), "load-progress-changed", G_CALLBACK (progress_change_cb), web_view);
    g_signal_connect (G_OBJECT (web_view), "load-committed", G_CALLBACK (load_commit_cb), web_view);
    g_signal_connect (G_OBJECT (web_view), "hovering-over-link", G_CALLBACK (link_hover_cb), web_view); 
	g_signal_connect (G_OBJECT (web_view), "print-requested", G_CALLBACK (print_requested_cb), web_view); 
	g_signal_connect (G_OBJECT (web_view), "navigation-requested", G_CALLBACK (navigation_requested_cb), NULL);

	
		
		#if 0
		//test by wyq
    g_signal_connect (G_OBJECT (web_view), "new-window-policy-decision-requested", G_CALLBACK (new_window_policy), web_view); 
		#endif
		
    return scrolled_window;
} 

static GtkWidget* create_statusbar ()
{	
    main_statusbar = GTK_STATUSBAR (gtk_statusbar_new ());
    status_context_id = gtk_statusbar_get_context_id (main_statusbar, "Link Hover"); 
	
    return (GtkWidget*)main_statusbar;
} 

static GtkWidget* create_toolbar ()
{
    GtkWidget* toolbar = gtk_toolbar_new (); 

    gtk_toolbar_set_orientation (GTK_TOOLBAR (toolbar), GTK_ORIENTATION_HORIZONTAL);
    gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH_HORIZ); 

    GtkToolItem* item; 

    /* the back button */
    item = gtk_tool_button_new_from_stock (GTK_STOCK_GO_BACK);
    g_signal_connect (G_OBJECT (item), "clicked", G_CALLBACK (go_back_cb), NULL);
    gtk_toolbar_insert (GTK_TOOLBAR (toolbar), item, -1); 

    /* The forward button */
    item = gtk_tool_button_new_from_stock (GTK_STOCK_GO_FORWARD);
    g_signal_connect (G_OBJECT (item), "clicked", G_CALLBACK (go_forward_cb), NULL);
    gtk_toolbar_insert (GTK_TOOLBAR (toolbar), item, -1); 

    button_stop = gtk_tool_button_new_from_stock (GTK_STOCK_STOP);
    g_signal_connect (G_OBJECT (button_stop), "clicked", G_CALLBACK (go_back_cb), NULL);
    gtk_toolbar_insert (GTK_TOOLBAR (toolbar), button_stop, -1); 

    /* The URL entry */
    item = gtk_tool_item_new ();
    gtk_tool_item_set_expand (item, TRUE);
    uri_entry = gtk_entry_new ();
    gtk_container_add (GTK_CONTAINER (item), uri_entry);
    g_signal_connect (G_OBJECT (uri_entry), "activate", G_CALLBACK (activate_uri_entry_cb), NULL);
    gtk_toolbar_insert (GTK_TOOLBAR (toolbar), item, -1); 

    /* The go button */
    item = gtk_tool_button_new_from_stock (GTK_STOCK_OK);
    g_signal_connect_swapped (G_OBJECT (item), "clicked", G_CALLBACK (activate_uri_entry_cb), (gpointer)uri_entry);
    gtk_toolbar_insert (GTK_TOOLBAR (toolbar), item, -1); 

    return toolbar;
} 

static GtkWidget* create_window ()
{
    GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		GdkScreen*  scr = gtk_window_get_screen( GTK_WINDOW( window));
		
		gtk_window_set_default_size( GTK_WINDOW( window), 
		gdk_screen_get_width( scr), 
		gdk_screen_get_height( scr));
 //   gtk_window_set_default_size (GTK_WINDOW (window), 1280, 720);
    gtk_widget_set_name (window, "GtkLauncher");
    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (destroy_cb), NULL); 

    return window;
} 

int main (int argc, char* argv[])
{
    gtk_init (&argc, &argv); 

    GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), create_toolbar (), FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), create_browser (), TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), create_statusbar (), FALSE, FALSE, 0); 

    main_window = create_window ();
    gtk_container_add (GTK_CONTAINER (main_window), vbox); 

    
	//WebKitWebSettings *setting = webkit_web_view_get_settings (WEBKIT_WEB_VIEW(web_view));
	//g_object_set (G_OBJECT(setting), "enable-developer-extras", TRUE, NULL);
	
   // gchar* uri = (gchar*) (argc > 1 ? argv[1] : "http://www.google.com.hk/");
    gchar* uri = "http://www.baidu.com";
    webkit_web_view_open (web_view, uri); 

    //const gchar* uri_test = webkit_web_view_get_uri (web_view);

    /*WebKitWebInspector *inspector = webkit_web_view_get_inspector (WEBKIT_WEB_VIEW(web_view));
	g_signal_connect (G_OBJECT (inspector), "inspect-web-view", G_CALLBACK(create_gtk_window_around_it), NULL);
    g_signal_connect (G_OBJECT (inspector), "show-window", G_CALLBACK(show_inpector_window), NULL);
    g_signal_connect (G_OBJECT (inspector), "notify::inspected-uri", G_CALLBACK(inspected_uri_changed_do_stuff), NULL);*/
    
    gtk_widget_grab_focus (GTK_WIDGET (web_view));
    gtk_widget_show_all (main_window);
   
    //const gchar* uri_test = webkit_web_view_get_uri (web_view);
    //printf("uri_main: %s\n", uri_test); 

    gtk_main (); 

    return 0;
}
