package org.apache.musicplf.presentation;

import org.apache.musicplf.domain.*;
import org.apache.musicplf.service.*;
import org.apache.musicplf.struts.*;
import com.ibatis.common.util.PaginatedList;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Collections;
import org.apache.struts.upload.FormFile;

public class SongBean extends BaseBean  
{
	private static final SongService songService = SongService.getInstance();
	private SongWithBLOBs songWithBlobs;
	private String sngName;
	private String songURL;
	private String workingSngName;
	private FormFile songFile;
	
	public SongBean() 
	{
		try 
		{
			songWithBlobs = new SongWithBLOBs();
		} 
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
	}
	
	public String getSngName()
    {
      return songWithBlobs.getSngName();
    }

    public void setSngName(String sngName) 
    {
      this.songWithBlobs.setSngName(sngName);
    }
    
    public String getSongURL()
    {
      return "../../util/jPlayer/mp3/"+workingSngName+".mp3";
    }

    public void setSongURL(String songURL) 
    {
      this.songURL = songURL;
    }
    
    public String getWorkingSngName()
    {
      return workingSngName;
    }

    public void setWorkingSngName(String workingSngName) 
    {
      this.workingSngName = workingSngName;
    }
    
    public FormFile getSongFile()
    {
      return songFile;
    }

    public void setSongFile(FormFile songFile) 
    {
      this.songFile=songFile;
    }
    
    public String uploadSong() 
    {
      try 
      {
          songWithBlobs.setSongFile(songFile.getFileData());
      	  songService.insertSong(songWithBlobs);
          return "success";
      } 
      catch (Exception e) 
      {
           e.printStackTrace();
           return null;
      }
    }
    
    public String getSongOrderByClicks() 
    {
      try 
      {
          songService.getSongOrderByClicks();
          return "success";
      } 
      catch (Exception e) 
      {
           e.printStackTrace();
           return null;
      }
    }
    
    public String play() 
    {
      try 
      {
         return "success";
      } 
      catch (Exception e) 
      {
           e.printStackTrace();
           return null;
      }
    }
}
