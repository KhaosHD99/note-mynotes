#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <cairo.h>

#include "cairodraw.h"
#include "fnAdvertisemenSkin.h"

static AdverDrawArea *curUser = NULL;	//记录当前使用者
/*************************************************************************************************
**on_expose_event_fadeout
**淡入淡出效果
**
**************************************************************************************************/
gboolean on_expose_event_Fadeout(GtkWidget * widget, GdkEventExpose * event, gpointer data)
{
	cairo_t *cr;
	static double alpha = 0.0;
	double const delta = 0.01;
//	static AdverDrawArea *curUser = NULL;	//记录当前使用者

	AdverDrawArea *drawArea;
	if(NULL == data)
	{
		printf("%s gpointer data null\r\n", __FUNCTION__);
		return FALSE;
	}
	else
		drawArea = (AdverDrawArea*)data;
	
	if(!drawArea->cariro_player.image)
	{
		printf("%s drawArea's cariro_player.image null\r\n", __FUNCTION__);
		return FALSE;
	}
	
	if(!drawArea->ad_darea || !drawArea->ad_darea->window)
	{
		printf("%s drawArea's ad_darea or ad_darea.window null\r\n", __FUNCTION__);
		return FALSE;
	}
	
	if(widget != drawArea->ad_darea)
	{
		printf("expose on differ widget [%s:%s]\r\n",
					gtk_widget_get_name(widget),
					gtk_widget_get_name(drawArea->ad_darea));
	}

	cr = gdk_cairo_create (drawArea->ad_darea->window);//gdk_cairo_create
	cairo_set_source_surface (cr, drawArea->cariro_player.image, 0, 0);
	
	if((curUser == NULL) || (drawArea == curUser))
	{
		curUser = drawArea;
		cairo_paint_with_alpha (cr, alpha);
		alpha += delta;
		if (alpha > 1)
		{	
			printf("cairo [%s] alpha paint over and delete timer %d!\r\n",
					drawArea->area_def_info.widget_name,
					drawArea->cariro_player.timer_id);
			gtk_timeout_remove(drawArea->cariro_player.timer_id);
			drawArea->cariro_player.timer_id = 0;
			drawArea->cariro_player.timer = FALSE;
			curUser = NULL;
			alpha = 0;
		}
		else
		{
			//printf("cairo [%s] paint alpha [%f]\r\n",
			//		drawArea->area_def_info.widget_name,
			//		alpha);
		}
/*
		if(drawArea->cariro_player.timer == FALSE)
		{
			alpha += delta;
			if (alpha >= 1)
			{	
				//drawArea->cariro_player.timer = TRUE;
			}
		}
		else
		{
			alpha -= delta;
			if (alpha <= 0)
			{	
				//drawArea->cariro_player.timer = FALSE;
			}
		}
*/
	}
	else
	{
		cairo_paint(cr);
		printf("\r\n");
//		printf("%s : [%s] using\r\n", __FUNCTION__, curUser->area_def_info.widget_name);
		printf("cairo [%s] paint drict : %s !\r\n",
						drawArea->area_def_info.widget_name,
						__FUNCTION__);
		
		drawArea->cariro_player.timer = FALSE;
		gtk_timeout_remove(drawArea->cariro_player.timer_id);
		drawArea->cariro_player.timer_id = 0;
	}

	cairo_destroy (cr);

	return FALSE;
}
/*************************************************************************************************
**on_expose_event_Vertical
**百叶窗模式
**
**************************************************************************************************/
gboolean on_expose_event_Vertical(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	cairo_t *cr;
	cairo_t *ic;

	cairo_surface_t *surface;

	static gdouble angle = 0;
	static gint w = 0;
	static gint h = 0;

	static gint image_width = 0;
	static gint image_height = 0;

	static gint count = 0;


	//gint width, height;

//	static AdverDrawArea *curUser = NULL;	//记录当前使用者

	AdverDrawArea *drawArea;
	if(NULL == data)
	{
		printf("%s gpointer data null\r\n", __FUNCTION__);
		return FALSE;
	}
	else
		drawArea = (AdverDrawArea*)data;
	
	if(!drawArea->cariro_player.image)
	{
		printf("%s drawArea's cariro_player.image null\r\n", __FUNCTION__);
		return FALSE;
	}
	
	if(!drawArea->ad_darea || !drawArea->ad_darea->window)
	{
		printf("%s drawArea's ad_darea or ad_darea.window null\r\n", __FUNCTION__);
		return FALSE;
	}
	
	if(widget != drawArea->ad_darea)
	{
		printf("expose on differ widget [%s:%s]\r\n",
					gtk_widget_get_name(widget),
					gtk_widget_get_name(drawArea->ad_darea));
	}

	cr = gdk_cairo_create(drawArea->ad_darea->window);

	//gtk_widget_get_size_request(drawArea->ad_darea, &width, &height);
	

	//  gtk_window_get_size(GTK_WINDOW(widget), &width, &height); 
	
	if((curUser == NULL) || (drawArea == curUser))
	{
		curUser = drawArea;
		surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, image_width, image_height);  

		image_width = cairo_image_surface_get_width(drawArea->cariro_player.image);
		image_height = cairo_image_surface_get_height(drawArea->cariro_player.image);

		w = image_width;  
		ic = cairo_create(surface);

		cairo_rectangle(ic, 0, 0, w, h);
		cairo_fill(ic);
		h += 1;
		if ( h == image_height)
		{
			printf("cairo [%s] Vertical paint over and delete timer %d!\r\n",
					drawArea->area_def_info.widget_name,
					drawArea->cariro_player.timer_id);
			gtk_timeout_remove(drawArea->cariro_player.timer_id);
			drawArea->cariro_player.timer_id = 0;
			drawArea->cariro_player.timer = FALSE;
			curUser = NULL;
			h = 0;
		}

		cairo_set_source_surface(cr, drawArea->cariro_player.image, 0, 0);
		cairo_mask_surface(cr, surface, 0, 0);

		cairo_surface_destroy(surface);
		cairo_destroy(cr);
		cairo_destroy(ic);
	}
	else
	{
		cairo_set_source_surface (cr, drawArea->cariro_player.image, 0, 0);
		cairo_paint(cr);
		printf("\r\n");
//		printf("%s : [%s] using\r\n", __FUNCTION__, curUser->area_def_info.widget_name);
		printf("cairo [%s] paint drict : %s !\r\n",
						drawArea->area_def_info.widget_name,
						__FUNCTION__);
		
		drawArea->cariro_player.timer = FALSE;
		gtk_timeout_remove(drawArea->cariro_player.timer_id);
		drawArea->cariro_player.timer_id = 0;
		cairo_destroy(cr);
	}
	return FALSE;
}

/*************************************************************************************************
**on_expose_event_Spectrum
**垂帘模式
**
**************************************************************************************************/
gboolean on_expose_event_Spectrum(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	cairo_t *cr;
	cairo_t *ic;
	cairo_surface_t *surface;
	static gdouble angle = 0;
	static gint w = 0;
	static gint h = 0;
	static gint image_width = 0;
	static gint image_height = 0;
	static gint count = 0;
//	static AdverDrawArea *curUser = NULL;	//记录当前使用者

//	gint width, height;

	AdverDrawArea *drawArea;
	if(NULL == data)
	{
		printf("%s gpointer data null\r\n", __FUNCTION__);
		return FALSE;
	}
	else
		drawArea = (AdverDrawArea*)data;
	
	if(!drawArea->cariro_player.image)
	{
		printf("%s drawArea's cariro_player.image null\r\n", __FUNCTION__);
		return FALSE;
	}
	
	if(!drawArea->ad_darea || !drawArea->ad_darea->window)
	{
		printf("%s drawArea's ad_darea or ad_darea.window null\r\n", __FUNCTION__);
		return FALSE;
	}
	
	if(widget != drawArea->ad_darea)
	{
		printf("expose on differ widget [%s:%s]\r\n",
					gtk_widget_get_name(widget),
					gtk_widget_get_name(drawArea->ad_darea));
	}

	cr = gdk_cairo_create(drawArea->ad_darea->window);
	
	//gtk_window_get_size(GTK_WINDOW(widget), &width, &height);
	//gtk_widget_get_size_request(drawArea->ad_darea, &width, &height);
	
	if((curUser == NULL) || (drawArea == curUser))
	{
		curUser = drawArea;
		surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, image_width, image_height);
		image_width = cairo_image_surface_get_width(drawArea->cariro_player.image);
		image_height = cairo_image_surface_get_height(drawArea->cariro_player.image);
		w = image_width;
		ic = cairo_create(surface);
		gint i, j;
		for (i = 0; i <= image_height; i+=7)
		{
			for (j=0 ; j < count; j++)
			{
				cairo_move_to(ic, 0, i+j);
				cairo_line_to(ic, w, i+j);
			}
		}
		count++;
		if ( count == 8)
		{
			printf("cairo [%s] Spectrum paint over and delete timer %d!\r\n",
					drawArea->area_def_info.widget_name,
					drawArea->cariro_player.timer_id);
			gtk_timeout_remove(drawArea->cariro_player.timer_id);
			drawArea->cariro_player.timer_id = 0;
			drawArea->cariro_player.timer = FALSE;
			curUser = NULL;
			count = 0;
		}
		cairo_stroke(ic);
		cairo_set_source_surface(cr, drawArea->cariro_player.image, 0, 0);
		cairo_mask_surface(cr, surface, 0, 0);
		cairo_surface_destroy(surface);
		cairo_destroy(cr);
		cairo_destroy(ic);
	}
	else
	{
		cairo_set_source_surface (cr, drawArea->cariro_player.image, 0, 0);
		cairo_paint(cr);
		printf("\r\n");
//		printf("%s : [%s] using\r\n", __FUNCTION__, curUser->area_def_info.widget_name);
		printf("cairo [%s] paint drict : %s !\r\n",
						drawArea->area_def_info.widget_name,
						__FUNCTION__);
		
		drawArea->cariro_player.timer = FALSE;
		gtk_timeout_remove(drawArea->cariro_player.timer_id);
		drawArea->cariro_player.timer_id = 0;
		cairo_destroy(cr);
	}
	return FALSE;
}
/*************************************************************************************************
**on_expose_event_Start
**星星模式
**
**************************************************************************************************/
static const int points[11][2] =
{
	{ 0, 85 },
	{ 75, 75 },
	{ 100, 10 },
	{ 125, 75 },
	{ 200, 85 },
	{ 150, 125 },
	{ 160, 190 },
	{ 100, 150 },
	{ 40, 190 },
	{ 50, 125 },
	{ 0, 85 }
};

gboolean on_expose_event_Start(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	cairo_t *cr;
	static gdouble angle = 0;
	static gdouble scale = 0;
	static gdouble alpha = 1;
	static gdouble delta = 0.01;

	gint width, height;

	AdverDrawArea *drawArea;
	if(NULL == data)
	{
		printf("%s gpointer data null\r\n", __FUNCTION__);
		return FALSE;
	}
	else
		drawArea = (AdverDrawArea*)data;

	if(!drawArea->cariro_player.image)
	{
		printf("%s drawArea's cariro_player.image null\r\n", __FUNCTION__);
		return FALSE;
	}
	
	if(!drawArea->ad_darea || !drawArea->ad_darea->window)
	{
		printf("%s drawArea's ad_darea or ad_darea.window null\r\n", __FUNCTION__);
		return FALSE;
	}
	
	if(widget != drawArea->ad_darea)
	{
		printf("expose on differ widget [%s:%s]\r\n",
					gtk_widget_get_name(widget),
					gtk_widget_get_name(drawArea->ad_darea));
	}

	cr = gdk_cairo_create(drawArea->ad_darea->window);
	//gtk_widget_get_size_request(drawArea->ad_darea, &width, &height);
	width = drawArea->cur_size.width;
	height = drawArea->cur_size.height;

	//printf("%s : [%d : %d]\r\n", __FUNCTION__, width, height);

	if(((curUser == NULL) || (drawArea == curUser)) && (scale < 0.99) )
	{
		curUser = drawArea;
////超炫效果
#if 0
		alpha = scale;
		cairo_pattern_t *spat =
    //cairo_pattern_create_linear(0, 0, 500, 360);
		cairo_pattern_create_radial(0, 0, 80,  500, 360, 20);
		cairo_pattern_add_color_stop_rgba(spat, 0,  0, 0, 0.8, alpha);
		cairo_pattern_add_color_stop_rgba(spat, 0.25,  1, 1, 0, alpha);
		cairo_pattern_add_color_stop_rgba(spat, 0.5,  0.9, 0.0, 0.0, alpha);
		cairo_pattern_add_color_stop_rgba(spat, 0.75,  0.8, 0.12, 0.56, alpha);
		cairo_pattern_add_color_stop_rgba(spat, 1,  0, 0, 0, alpha);
		
		cairo_set_source (cr, spat);
		cairo_paint(cr);	
#endif

		cairo_set_source_rgb(cr, 0, 0.44, 0.7);
		cairo_set_line_width(cr, 1);
		cairo_translate(cr, width / 2, height / 2 );
		cairo_rotate(cr, angle);
		cairo_scale(cr, scale, scale);
		gint i;
		for ( i = 0; i < 10; i++ )
		{
			cairo_line_to(cr, points[i][0], points[i][1]);
		}
		cairo_close_path(cr);
		cairo_fill(cr);
		cairo_stroke(cr);
/*
		if ( scale < 0.01 )
		{
			delta = -delta;
		}
		else if (scale > 0.99)
		{
			delta = -delta;
		}
		scale += delta;
		angle += 0.01;
*/
		if ( scale > 0.99 )
		{
/*
			printf("cairo [%s] Spectrum paint over and delete timer %d!\r\n",
					drawArea->area_def_info.widget_name,
					drawArea->cariro_player.timer_id);
			gtk_timeout_remove(drawArea->cariro_player.timer_id);
			drawArea->cariro_player.timer_id = 0;
			drawArea->cariro_player.timer = FALSE;
			curUser = NULL;
			scale = 1;
*/
		}
		else
		{
			scale += delta;
			angle += 0.01;
		}
		
		cairo_destroy(cr);
	}
	else
	{
		cairo_set_source_surface (cr, drawArea->cariro_player.image, 0, 0);
		cairo_paint(cr);
		printf("\r\n");
//		printf("%s : [%s] using\r\n", __FUNCTION__, curUser->area_def_info.widget_name);
		printf("cairo [%s] paint drict : %s !\r\n",
						drawArea->area_def_info.widget_name,
						__FUNCTION__);
		
		drawArea->cariro_player.timer = FALSE;
		gtk_timeout_remove(drawArea->cariro_player.timer_id);
		drawArea->cariro_player.timer_id = 0;
		cairo_destroy(cr);
		if(curUser == drawArea)
			curUser = NULL;
		scale = 0;
	}
	return FALSE;
}

/*************************************************************************************************
**on_expose_event_rollText
**滚条模式
**
**************************************************************************************************/
#include<malloc.h>
gboolean IsTextUTF8(char* str,unsigned int length);
unsigned int getUTF8WordLen(char* str,unsigned int length);
char **new_cairo_sub_string(cairo_t *cr, unsigned int width, const char* str_message, int *count)
{
		#define MAX_SUB_SIZE 1024

		char **subs = NULL;
		char *str_tmp = NULL;
		cairo_text_extents_t te;
		cairo_font_extents_t fe;
		
		if(cr == NULL || str_message == NULL || strlen(str_message) == 0 ||width <= 0)
		{
			g_warning("%s parses nullr\\n", __FUNCTION__);
			return NULL;	
		}
		
		subs = (char**)malloc(sizeof(char*)*MAX_SUB_SIZE);
		
		cairo_font_extents(cr, &fe);	
		cairo_text_extents(cr, "a", &te);	

		int sub_len = (width/(te.width-fe.descent));
				
		str_tmp = (char*)malloc(sizeof(char)*(strlen(str_message)+1));
		
		int char_count = 0;
		int char_index = 0;
		int word_len = 0;
		int substr_star = 0;
		int substr_count = 0;

		for( char_index = 0; char_index < strlen(str_message);)
		{
				char *sub = (str_message + char_index);
				word_len = getUTF8WordLen(sub, strlen(sub));
				if(word_len <= 0)
				{
					g_warning("get utf8 word error @ str[%d]\r\n", char_index);
					break;	
				}

				char_count++;
				char_index += word_len;

				strncpy(str_tmp, str_message+substr_star, char_index-substr_star);
				str_tmp[char_index-substr_star] = '\0';
				cairo_text_extents(cr, str_tmp, &te);
				unsigned char chr = *sub;
				if(te.width > (double)(width) || chr == '\r' || chr == '\n')
				{
					int len = char_index-substr_star-word_len;
					
					subs[substr_count] = (char*)malloc(sizeof(char)*(len+1));;
					strncpy(subs[substr_count], str_message+substr_star, len);
					subs[substr_count][len] = '\0';

					//update char_index
					//check new line flag;
					if(te.width > (double)(width))
					{
						//仅满值
						char_index = char_index-word_len;
					}
					else
					{
						char_index = char_index-word_len;

						int leftlen = strlen(str_message) - char_index;
	
						while(*sub != '\0')
						{
								if((*sub == '\r' || *sub == '\n'))
								{
										//printf("get new line flag : %d\r\n", *sub);
										char_index++;
								}
								else
									if(*sub == '\0')
									{
											char_index++;	//标记其最后一位
											//printf("+++++++++++++++++++++++++get the end line flag : %d\r\n", *sub);
											break;
									}
									else
									{
											//printf("new sub start @ : %d\r\n", char_index);
											break;
									}
								sub++;
						}
					}

					substr_count++;
					substr_star = char_index;
					char_count = 0;
					
					if(MAX_SUB_SIZE == substr_count)
					{
						printf("too much sub strs [%d:%d], stop creat new sub strings\r\n", MAX_SUB_SIZE, substr_count);
						break;	
					}
				}
				else
					if(char_index >= strlen(str_message))
					{
						int len = char_index-substr_star;
						subs[substr_count] = (char*)malloc(sizeof(char)*(len+1));;
						strncpy(subs[substr_count], str_message+substr_star, len);
						subs[substr_count][len] = '\0';
	
						substr_count++;
						break;
					}
		}
		*count = substr_count;
		if(count == 0)
		{
			free(subs);
			subs = NULL;
			g_warning("%s : get count 0\r\n", __FUNCTION__);
		}
		free(str_tmp);	
		return subs;		
}

gboolean on_expose_event_rollText(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	cairo_t *cr;


	gint win_width, win_height;
	static gdouble x = 0, y = 0;
  const gdouble del = 0;
	//gtk_window_get_size(GTK_WINDOW(widget), &width, &height);
	//gtk_widget_get_size_request(widget, &width, &height);
	//printf("%s play on : %s\r\n", __FUNCTION__, gtk_widget_get_name(widget));

	AdverDrawArea *drawArea;
	if(NULL == data)
	{
		printf("%s gpointer data null\r\n", __FUNCTION__);
		return FALSE;
	}
	else
		drawArea = (AdverDrawArea*)data;
/*
	if(!drawArea->cariro_player.image)
	{
		printf("%s drawArea's cariro_player.image null\r\n", __FUNCTION__);
		return FALSE;
	}
*/	
	if(!drawArea->ad_darea || !drawArea->ad_darea->window)
	{
		printf("%s drawArea's ad_darea or ad_darea.window null\r\n", __FUNCTION__);
		return FALSE;
	}
	
	if(widget != drawArea->ad_darea)
	{
		printf("expose on differ widget [%s:%s]\r\n",
					gtk_widget_get_name(widget),
					gtk_widget_get_name(drawArea->ad_darea));
	}

	if(((curUser == NULL) || (drawArea == curUser)))
	{
		curUser = drawArea;
		cr = gdk_cairo_create(drawArea->ad_darea->window);
		//gtk_widget_get_size_request(drawArea->ad_darea, &width, &height);
		win_width = drawArea->cur_size.width;
		win_height = drawArea->cur_size.height;
		if(!drawArea->cariro_player.image)
		{
	//颜色底		
			cairo_set_source_rgb(cr, 0.5, 0, 0);
			cairo_paint(cr);
		}
		else
		{
			cairo_set_source_surface (cr, drawArea->cariro_player.image, 0, 0);
			cairo_paint(cr);
		}

		cairo_select_font_face(cr, "SimSun", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
		cairo_set_font_size(cr, 20.0);

//		cairo_set_source_rgb(cr, 1, 1, 1);
		cairo_set_source_rgb(cr, 0.8, 0.48, 0.0);
		cairo_text_extents_t te;
		cairo_font_extents_t fe;
		//显示之前需先转换成utf8
//		char str_message[] =  "  1泛网字幕滚动条泛网字幕滚动条泛网字幕滚动条泛网字幕滚动条泛网字幕滚动条\r\n2泛网字幕滚动....\r\n		再见!";
		char str_message[] = "	中俄火星探测合作谈判参与者、上海航天技术研究院卫星总师徐博明研究员21日在北京航天城举行的主题为“火星探测”的第三届中国空间技术论坛上透露，中俄联合探测火星工程俄方“火卫一，土壤样品返回”空间飞行器(又称“福布斯”探测器)与中方“萤火一号”火星探测器，预计2011年11月由俄运载火箭同时发射。";
		//asii 1, 2;
		//utf8 UFT8可用1-6,1的话一般为单字符
		cairo_font_extents(cr, &fe);
		cairo_text_extents(cr, str_message, &te);	
		
		int count = 0;
		char **subs = new_cairo_sub_string(cr, win_width, str_message, &count);
		if(subs == NULL || count <= 0)
		{
			if(subs != NULL)
			{
				free(subs);
				g_warning("get subs not null ,but count = %d\r\n", count);			
			}
			cairo_destroy(cr);
			return FALSE;
		}
		
		int i = 0;
		static int read_index = 0;
		double diffVal = (double)(win_height-te.height)/2;

		static int h = 0;
		
		count += 1;		//人为的增加一条，使得最后一条同样能渐渐小时，在显示非第一条时需检测溢出
		if(count == 1)
		{
			//由于人为的增加了一条，故count>1永远有效
			//无需处理真实条数为1的情况
		}
		else
		{
			if(read_index%count == 0)
			{
				int tmp_y = win_height + te.height + diffVal + h;
				
				cairo_move_to(cr, 0, tmp_y);
				cairo_show_text(cr, subs[0]);
			}
			else
			if(read_index%count > 0 && read_index%count <= count-1)
			{
				//当前显示区域可见条目个数为2条(仅能满足完全显示一条),但能完全显示多条时，其处理方法有变
				int tmp_y = te.height + diffVal + h;
				cairo_move_to(cr, 0, tmp_y);
				cairo_show_text(cr, subs[read_index%count -1]);
				
				//由于人为的增加了一条，故测试是否越界
				if(read_index%count < (count -1))
				{
					tmp_y = win_height + te.height + diffVal + h;	
					cairo_move_to(cr, 0, tmp_y);
					cairo_show_text(cr, subs[read_index%count]); //read_index == count-1是无效的
				}
			}
			//释放资源
			for(i = 0; i< (count-1);i++)
			{
				free(subs[i]);
				subs[i] = NULL;	
			}
			free(subs);
			subs = NULL;
		}

		h--;
		if((h + win_height) == 0)
		{
			drawArea->cariro_player.timer = FALSE;
			gtk_timeout_remove(drawArea->cariro_player.timer_id);
			drawArea->cariro_player.timer_id = 0;
			curUser = NULL;
			printf("mid index : %d, and end @ : %f\r\n", read_index%count, win_height + te.height + diffVal + h);
			read_index++;
			h = 0;
		}
				
		cairo_destroy(cr);

	}
	else
	{
		if(!drawArea->cariro_player.image)
		{
			cairo_set_source_surface (cr, drawArea->cariro_player.image, 0, 0);
			cairo_paint(cr);
			printf("\r\n");
			printf("cairo [%s] paint drict : %s !\r\n",
							drawArea->area_def_info.widget_name,
							__FUNCTION__);
			
			drawArea->cariro_player.timer = FALSE;
			gtk_timeout_remove(drawArea->cariro_player.timer_id);
			drawArea->cariro_player.timer_id = 0;
			cairo_destroy(cr);
			y = 0;
		}
		
	}
		
	return FALSE;
}

unsigned int getUTF8WordLen(char* str,unsigned int length)
{
	if(str == NULL || length <= 0)
	{
		printf("NULL STR : %d \r\n", length);	
		return 0;
	}
	
	unsigned char chr = *str;

	unsigned int nBytes=0;//UFT8可用1-6个字节编码,ASCII用一个字节

	if( (chr&0x80) == 0 ) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx
	{
			nBytes=1;
			return nBytes;
	}
	if(chr>=0x80)
	{
		if(chr>=0xFC&&chr<=0xFD)
			nBytes=6;
		else if(chr>=0xF8)
			nBytes=5;
		else if(chr>=0xF0)
			nBytes=4;
		else if(chr>=0xE0)
			nBytes=3;
		else if(chr>=0xC0)
			nBytes=2;
		else
		{
			printf("unknow bytes len :%d\r\n", nBytes);
			return nBytes = 1;
		}
		return nBytes;
	}
}


gboolean IsTextUTF8(char* str,unsigned int length)
{
	int i;
	unsigned int nBytes=0;//UFT8可用1-6个字节编码,ASCII用一个字节
	unsigned char chr;
	gboolean bAllAscii=TRUE; //如果全部都是ASCII, 说明不是UTF-8
	for( i=0 ; i<length; i++)
	{
		chr= *(str+i);
		if( (chr&0x80) != 0 ) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx
			bAllAscii= FALSE;
		if(nBytes==0) //如果不是ASCII码,应该是多字节符,计算字节数
		{
			if(chr>=0x80)
			{
				if(chr>=0xFC&&chr<=0xFD)
					nBytes=6;
				else if(chr>=0xF8)
					nBytes=5;
				else if(chr>=0xF0)
					nBytes=4;
				else if(chr>=0xE0)
					nBytes=3;
				else if(chr>=0xC0)
					nBytes=2;
				else
				{
					return FALSE;
				}
				nBytes--;
			}
		}
		else //多字节符的非首字节,应为 10xxxxxx
		{
			if( (chr&0xC0) != 0x80 )
			{
				return FALSE;
			}
			nBytes--;
		}
	}

	if( nBytes > 0 ) //违返规则
	{
		return FALSE;
	}
	if( bAllAscii ) //如果全部都是ASCII, 说明不是UTF-8
	{
		return FALSE;
	}
	return TRUE;
} 
