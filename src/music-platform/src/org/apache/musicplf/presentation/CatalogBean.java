package org.apache.musicplf.presentation;

import com.ibatis.common.util.PaginatedList;
import org.apache.musicplf.domain.Category;
import org.apache.musicplf.domain.Song;
import org.apache.musicplf.service.*;
import org.apache.musicplf.struts.ActionContext;
import org.apache.musicplf.struts.BaseBean;

public class CatalogBean extends BaseBean {

  /* Constants */
  private static final CatalogService catalogService = CatalogService.getInstance();
  private static final SongService songService = SongService.getInstance();
  
  /* Private Fields */
  private String keyword;
  private String pageDirection;
  private String name;
  private int categoryId;
  private Category category;
  private PaginatedList categoryList;
  private String sngname;
  private Song song;
  private PaginatedList songList;
  private String itemId;
  private PaginatedList itemList;
  private int resultNum;

  /* JavaBeans Properties */
  public int getResultNum() 
  {
    return songList.size();
  }

  public void setResultNum(int resultNum) 
  {
    this.resultNum = resultNum;
  }
  
  public String getKeyword() 
  {
    return keyword;
  }

  public void setKeyword(String keyword) 
  {
    this.keyword = keyword;
  }

  public String getPageDirection() 
  {
    return pageDirection;
  }

  public void setPageDirection(String pageDirection)
  {
    this.pageDirection = pageDirection;
  }

  public int getCategoryId()
  {
    return categoryId;
  }

  public void setCategoryId(int categoryId) 
  {
    this.categoryId = categoryId;
  }

  public String getSngname()
  {
    return sngname;
  }

  public void setSngname(String sngName) 
  {
    this.sngname = sngName;
  }

  public String getItemId() 
  {
    return itemId;
  }

  public void setItemId(String itemId)
  {
    this.itemId = itemId;
  }

  public Category getCategory()
  {
    return category;
  }

  public void setCategory(Category category) 
  {
    this.category = category;
  }

  public Song getSong() 
  {
    return song;
  }

  public void setSong(Song song) 
  {
    this.song = song;
  }

  

 

  public PaginatedList getCategoryList()
  {
    return categoryList;
  }

  public void setCategoryList(PaginatedList categoryList) 
  {
    this.categoryList = categoryList;
  }

  public PaginatedList getSongList()
  {
    return songList;
  }

  public void setSongList(PaginatedList songList)
  {
    this.songList = songList;
  }

  public PaginatedList getItemList() 
  {
    return itemList;
  }

  public void setItemList(PaginatedList itemList)
  {
    this.itemList = itemList;
  }

  /* Public Methods */
  
  public String viewLeaderBoard()
  {
	  try
	  {
		  songList = songService.getSongOrderByClicks();
		  return "success";
	  }
	  catch(Exception ex)
	  {
		  System.out.println("got ex");
		  ex.printStackTrace();
		  return null;
	  }
  }

  public String viewCategory()
  {
	  try
	  {
         if (categoryId > -1) 
         {
        	 System.out.println("categoryid>1");
             songList = catalogService.getSongListByCategoryId(categoryId);
             category = catalogService.getCategoryById(categoryId);
         }
         return "success";
	  }
	  catch(Exception ex)
	  {
		  System.out.println("got ex");
		  ex.printStackTrace();
		  return null;
	  }
	  
  }

  public String searchSongsWithDetails()
  {
    if (keyword == null || keyword.length() < 1)
    {
      System.out.println("keyword is nothing");
      ActionContext.getActionContext().setSimpleMessage("Please enter a keyword to search for, then press the search button.");
      return "failure";
    } 
    else 
    {
      System.out.println("got keyword:"+keyword);
      songList = catalogService.searchSongListByDetails(keyword.toLowerCase());
      return "success";
    }
  }
  
  public String searchSongs()
  {
    if (keyword == null || keyword.length() < 1)
    {
      System.out.println("keyword is nothing");
      ActionContext.getActionContext().setSimpleMessage("Please enter a keyword to search for, then press the search button.");
      return "failure";
    } 
    else 
    {
      System.out.println("got keyword:"+keyword);
      songList = catalogService.searchSongList(keyword.toLowerCase());
      return "success";
    }
  }

  public String switchProductListPage() 
  {
    if ("next".equals(pageDirection)) 
    {
    	songList.nextPage();
    } 
    else if ("previous".equals(pageDirection))
    {
    	songList.previousPage();
    }
    return "success";
  }

  public String switchItemListPage() 
  {
    if ("next".equals(pageDirection))
    {
      itemList.nextPage();
    }
    else if ("previous".equals(pageDirection)) 
    {
      itemList.previousPage();
    }
    return "success";
  }



  public void clear () 
  {
    keyword = null;
    pageDirection = null;

    name = null;
    category = null;
    categoryList = null;

    sngname = null;
    song = null;
    songList = null;

    itemId = null;
    itemList = null;
  }

}
