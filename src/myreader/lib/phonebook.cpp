#include <unistd.h>
#include <stdlib.h>

#include "lpconfig.h"

#ifdef HAVE_GLIB
#include <glib.h>
#else
#include "uglib.h"
#endif

#include "mcallconfig.h"

static GList *mcallinks = NULL;

int write_mcall_item(struct _LpConfig *config, MediaFileInfo *item, int index);

const gchar *__playarea_enum_to_str(int enum_val);
const gchar *__playtype_enum_to_str(int enum_val);
PlayArea __playarea_str_to_enum(const gchar *enum_str);
MediaCallType __playtype_str_to_enum(const gchar *enum_str);
int get_mcall_file_define(struct _LpConfig *config, const char *section, MediaFileInfo *obj, MediaCallType playtype);

MediaFileInfo* mcallitem_new_from_config_file(struct _LpConfig *config, int index);


const gchar *__playarea_enum_to_str(int enum_val)
{
	switch(enum_val)
	{
	case AREA_A :
		return "AREA_A";
		break;
	case AREA_B :
		return "AREA_B";
		break;
	case AREA_C :
		return "AREA_C";
		break;
	case AREA_D :
		return "AREA_D";
		break;
	}
	g_warning("Invalid playarea enum value. %d", enum_val);
	return "NULL";
}

const gchar *__playtype_enum_to_str(int enum_val)
{
	switch(enum_val)
	{
	case PIC_ONLY:
		return "PIC_ONLY";
		break;
	case VID_ONLY:
		return "VID_ONLY";
		break;
	case GIF_ONLY:
		return "GIF_ONLY";
		break;
	case AUD_ONLY:
		return "AUD_ONLY";
		break;
	case PIC_AUD:
		return "PIC_AUD";
		break;
	case VID_AUD:
		return "VID_AUD";
		break;
	case GIF_AUD:
		return "GIF_AUD";
		break;
	}
	g_warning("Invalid playtype enum value.");
	return "NULL";
}

PlayArea __playarea_str_to_enum(const gchar *enum_str)
{
	if(strcmp(enum_str, "AREA_A") == 0)
		return AREA_A;

	if(strcmp(enum_str, "AREA_B") == 0)
		return AREA_B;

	if(strcmp(enum_str, "AREA_C") == 0)
		return AREA_C;

	if(strcmp(enum_str, "AREA_D") == 0)
		return AREA_D;
		
	g_warning("Invalid playarea enum value %s", enum_str);
	return (PlayArea)-1;
}


MediaCallType __playtype_str_to_enum(const gchar *enum_str)
{
	if(strcmp(enum_str, "PIC_ONLY") == 0)
		return PIC_ONLY;

	if(strcmp(enum_str, "VID_ONLY") == 0)
		return VID_ONLY;

	if(strcmp(enum_str, "GIF_ONLY") == 0)
		return GIF_ONLY;

	if(strcmp(enum_str, "AUD_ONLY") == 0)
		return AUD_ONLY;
		
	if(strcmp(enum_str, "PIC_AUD") == 0)
		return PIC_AUD;

	if(strcmp(enum_str, "VID_AUD") == 0)
		return VID_AUD;

	if(strcmp(enum_str, "GIF_AUD") == 0)
		return GIF_AUD;

	g_warning("Invalid playtype enum value %s", enum_str);
	return (MediaCallType)-1;
}


int get_mcall_file_define(struct _LpConfig *config, const char *section, MediaFileInfo *obj, MediaCallType playtype)
{
	const gchar *tmpfile;

	switch(playtype)
	{
		case PIC_ONLY:
		case GIF_ONLY:
			tmpfile = lp_config_get_string(config, section,"jpegfile",NULL);
			g_message("jpegfile  : %s", tmpfile);
			if(tmpfile == NULL || strlen(tmpfile) >= MAX_FILE_NAME)
			{
				if(tmpfile == NULL)
					g_error("can not find jpegfile define!");
				else
					g_error("jpegfile name len too length %d", strlen(tmpfile));
				return -1;
			}
			else
			{
				strcpy(obj->szJpegFile, tmpfile);
			}
			break;
		case VID_ONLY:
			tmpfile = lp_config_get_string(config, section,"videofile",NULL);
			g_message("videofile  : %s", tmpfile);
			if(tmpfile == NULL || strlen(tmpfile) >= MAX_FILE_NAME)
			{
				if(tmpfile == NULL)
					g_error("can not find videofile define!");
				else
					g_error("videofile name len too length %d", strlen(tmpfile));
				return -1;
			}
			else
			{
				strcpy(obj->szVideoFile, tmpfile);
			}
			break;
		case AUD_ONLY:
			tmpfile=lp_config_get_string(config, section,"audiofile",NULL);
			if(tmpfile == NULL || strlen(tmpfile) >= MAX_FILE_NAME)
			{
				if(tmpfile == NULL)
					g_error("can not find audiofile define!");
				else
					g_error("audiofile name len too length %d", strlen(tmpfile));
				return -1;
			}
			else
			{
				g_message("audio      : %s", tmpfile);
				strcpy(obj->szAudioFile, tmpfile);
			}
			break;
		default:
			g_warning("Invalid playarea enum value %d", playtype);
			return -1;			
	}
	return 0;
}	

int write_mcall_item(struct _LpConfig *config, MediaFileInfo *item, int index)
{
	gchar key[50];
	gchar *tmp;
	int a;
	if(index != item->nFileID)
	{
		g_warning("item_nFileID != write index : [%d, %d]", item->nFileID, index);
	}

	sprintf(key,"mcall_%i",index);
	
	lp_config_set_int(config, key, "index", index);

	lp_config_set_string(config, key, "playarea", __playarea_enum_to_str(item->mPlayArea));
	
	lp_config_set_string(config, key, "playtype", __playtype_enum_to_str(item->nMCallType));

	lp_config_set_string(config, key, "jpegfile", item->szJpegFile);
	lp_config_set_string(config, key, "videofile", item->szVideoFile);
	lp_config_set_string(config, key, "audiofile", item->szAudioFile);
	return 0;
}


MediaFileInfo* mcallitem_new_from_config_file(struct _LpConfig *config, int index)
{
	gint mcallindex;
	const gchar *tmp;
	gchar item[50];
	MediaFileInfo *obj;
	
	sprintf(item,"mcall_%i",index);
	
	if (!lp_config_has_section(config, item))
	{
		g_error("find %s error\r\n", item);
		return NULL;
	}
	obj = g_new0(MediaFileInfo,1);
	memset(obj, 0, sizeof(MediaFileInfo));

	mcallindex =lp_config_get_int(config,item,"index",index);
	g_message("mcallindex : %d", mcallindex);
	
	obj->nFileID = mcallindex;

	tmp=lp_config_get_string(config,item,"playarea",NULL);
	g_message("playarea   : %s", tmp);

	obj->mPlayArea = __playarea_str_to_enum(tmp);
	if((int)(obj->mPlayArea) == -1)
	{
		free(obj);
		return NULL;
	}
	tmp=lp_config_get_string(config,item,"playtype",NULL);
	g_message("playtype   : %s", tmp);

	obj->nMCallType = __playtype_str_to_enum(tmp);

	if((int)(obj->nMCallType) == -1)
	{
		free(obj);
		return NULL;
	}

	switch(obj->nMCallType)
	{
		case PIC_ONLY:
		case GIF_ONLY:
			if(get_mcall_file_define(config, item, obj, PIC_ONLY) != 0)
			{
				free(obj);
				return NULL;
			}
			break;
		case VID_ONLY:
			if(get_mcall_file_define(config, item, obj, VID_ONLY) != 0)
			{
				free(obj);
				return NULL;
			}
			break;
		case AUD_ONLY:
			if(get_mcall_file_define(config, item, obj, AUD_ONLY) != 0)
			{
				free(obj);
				return NULL;
			}
			break;
		case PIC_AUD:
		case GIF_AUD:
			if(get_mcall_file_define(config, item, obj, PIC_ONLY) != 0)
			{
				free(obj);
				return NULL;
			}

			if(get_mcall_file_define(config, item, obj, AUD_ONLY) != 0)
			{
				free(obj);
				return NULL;
			}
			break;
		case VID_AUD:
			if(get_mcall_file_define(config, item, obj, VID_ONLY) != 0)
			{
				free(obj);
				return NULL;
			}
			if(get_mcall_file_define(config, item, obj, AUD_ONLY) != 0)
			{
				free(obj);
				return NULL;
			}
			break;
		default:
			g_warning("Invalid playtype enum value. %d", obj->nMCallType);
			free(obj);
			return NULL;
	}

	g_message("");

	return obj;
}



void mcall_config_read(struct _LpConfig *config)
{	
	int i;
	GList *contactsList;
	MediaFileInfo* mi;
	if(config == NULL)
	{
		g_error("_LpConfig = (null)");
		return ;
	}
	delete_mcallink();
	for (i=0;(mi = mcallitem_new_from_config_file(config,i)) != NULL;i++)
	{
		mcallinks = g_list_append(mcallinks,(gpointer)mi);
	}
	//return contactsList;
}


int save_mcall_configs(struct _LpConfig *config)
{
	int i;
	int counts;
	int writeindex = 0;

	if(config == NULL)
	{
		g_error("_LpConfig = (null)");
		return -1;
	}

	if(mcallinks == NULL)
	{
		g_error("no mcall links, save mcalls error!");
		return -1;
	}
	
	counts = g_list_length(mcallinks);

	if(counts <= 0)
	{
		g_warning("empty mcall link!");
		return -1;
	}
		
	for(i = 0; i < counts; i++)
	{
		write_mcall_item(config, (MediaFileInfo *)g_list_nth_data(mcallinks, i), i);
	}

	return lp_config_sync(config);
}



int get_mcallitem_counts()
{
	if(mcallinks != NULL)
		return g_list_length(mcallinks);
	else
	{
		g_error("no mcall links");
		return -1;
	}
}

MediaFileInfo *get_mcallitem_by_index(int index)
{
	MediaFileInfo *ptmp;
	static MediaFileInfo mi;
	if(mcallinks != NULL)
	{
		ptmp = (MediaFileInfo *)g_list_nth_data(mcallinks, index);
		if(ptmp != NULL)
		{
			memcpy(&mi, ptmp, sizeof(MediaFileInfo));
			return &mi;
		}
		else
			return NULL;
	}
	else
	{
		g_error("no mcall links");
		return NULL;
	}
}

int delete_mcallink()
{
	int i = 0;
	int counts = 0;
	if(mcallinks == NULL)
	{
		g_error("no mcall links");
		return -1;
	}
	else
	{
		counts = g_list_length(mcallinks);
		for(i = 0; i < counts; i++)
		{
			g_message("delete mcall items : %d", i);
			g_free((MediaFileInfo *)g_list_nth_data(mcallinks, i));
		}
		g_list_free(mcallinks);
		mcallinks = NULL;
	}
}

