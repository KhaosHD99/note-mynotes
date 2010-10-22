package org.apache.musicplf.service;

import com.ibatis.common.util.PaginatedList;
import org.apache.musicplf.domain.*;
import org.apache.musicplf.persistence.sqlmapdao.*;
import org.apache.musicplf.persistence.sqlmapdao.AccountDAOImpl;

public class SongService 
{
	 //Constants 
	  private static final SongService instance = new SongService();
	  private static SongDAOImpl songDAOImpl = new SongDAOImpl();
	 
	  //Constructors
	  public SongService()
	  {
		
	  }

	  //Public Methods
	  public static SongService getInstance()
	  {
	    return instance;
	  }

	  //Song
	 
      public void insertSong(SongWithBLOBs song) 
	  {
		  songDAOImpl.intserSong(song);
	  }
      
      public PaginatedList getSongOrderByClicks()
      {
    	  return songDAOImpl.getSongOrderByClicks();
      }

}
