package org.apache.musicplf.service;

import com.ibatis.common.util.PaginatedList;
import com.ibatis.common.resources.Resources; 
import com.ibatis.sqlmap.client.SqlMapClient; 
import com.ibatis.sqlmap.client.SqlMapClientBuilder; 
import org.apache.musicplf.domain.Category;
import org.apache.musicplf.domain.Song;
import org.apache.musicplf.persistence.sqlmapdao.*;
import java.util.List;

public class CatalogService 
{
  /* Constants */
  private static final CatalogService instance = new CatalogService();
  private static AccountDAOImpl accountDAOImpl = new AccountDAOImpl();
  private static CategoryDAOImpl categoryDAOImpl = new CategoryDAOImpl();
  private static SongDAOImpl songDAOImpl = new SongDAOImpl();
 
  /* Constructors */
  private CatalogService() 
  {
	
  }

  /* Public Methods */
  public static CatalogService getInstance() 
  {
    return instance;
  }

  /* CATEGORY */
  public List getCategoryList() 
  {
     return null;
  }

  public Category getCategoryById(int categoryId)
  {
      return categoryDAOImpl.getCategoryById(categoryId);
  }

  //Song
  public Song getSongById(int Id) 
  {
    return songDAOImpl.getSongById(Id);
  }
  
  public PaginatedList searchSongListByDetails(String categoryId) 
  {
    return songDAOImpl.searchSongListWithDetails(categoryId);
  }

  public PaginatedList searchSongList(String keywords) 
  {
    return songDAOImpl.searchSongList(keywords);
  }
  
  public PaginatedList searchSongWithCategory(String keywords) 
  {
    return songDAOImpl.searchSongList(keywords);
  }
  
  public PaginatedList getSongListByCategoryId(int categoryId)
  {
	    return songDAOImpl.getSongListByCategoryId(categoryId); 
  }
}