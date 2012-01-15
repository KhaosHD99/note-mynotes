package org.apache.musicplf.persistence.sqlmapdao;

import com.ibatis.common.util.PaginatedList;
import com.ibatis.common.resources.Resources; 
import com.ibatis.sqlmap.client.SqlMapClient; 
import com.ibatis.sqlmap.client.SqlMapClientBuilder; 
import com.ibatis.sqlmap.client.SqlMapClient;
import java.io.Reader;
import java.nio.charset.Charset;
import java.sql.SQLException;
import java.util.List;
import java.util.ArrayList;
import java.util.StringTokenizer;
import org.apache.musicplf.domain.*;

public class SongDAOImpl  
{
    private SqlMapClient sqlMapClient;
    protected static final int PAGE_SIZE = 4;
    
    public SongDAOImpl() 
    {
        super();
        try
        {
           Resources.setCharset(Charset.forName("UTF-8"));
  	       Reader reader = Resources.getResourceAsReader("org/apache/musicplf/persistence/sqlmapdao/sql/sql-map-config.xml"); 
  	       sqlMapClient = SqlMapClientBuilder.buildSqlMapClient(reader); 
  	       reader.close(); 
        }
        catch(Exception ex)
      	{
           ex.printStackTrace();
        }
    }

    public void intserSong(SongWithBLOBs songWithBlobs)
    {
    	try
    	{
    	//   System.out.println("songId:"+id);
           sqlMapClient.insert("song.insertSongWithBLOBs", songWithBlobs);
        }
    	catch(Exception ex)
    	{
    		ex.printStackTrace();
    		
    	}
    	
    }
    
    public Song getSongById(int id)
    {
    	try
    	{
    	   System.out.println("songId:"+id);
           return (Song)sqlMapClient.queryForList("song.getSongById", id).get(0);
        }
    	catch(Exception ex)
    	{
    		ex.printStackTrace();
    		return null;
    	}
    	
    }
    
    public PaginatedList getSongListByCategoryId(int categoryId)
    {
    	try
    	{
           return sqlMapClient.queryForPaginatedList("song.getSongListByCategoryId", categoryId, PAGE_SIZE);
        }
    	catch(Exception ex)
    	{
    		ex.printStackTrace();
    		return null;
    	}
    	
    }

    public PaginatedList getSongOrderByClicks()
    {
    	try
    	{
    	    return sqlMapClient.queryForPaginatedList("song.getSongOrderByClicks",PAGE_SIZE);
        }
    	catch(Exception ex)
    	{
    		ex.printStackTrace();
    		return null;
    	}
    	
    }
    
     public PaginatedList searchSongList(String keywords) 
    {
    	try
      	{
            Object parameterObject = new SongSearch(keywords);
            if(sqlMapClient==null)
            	System.out.println("sqlMapClient is null");
            else 
            	System.out.println("smc is not null");
        	return sqlMapClient.queryForPaginatedList("song.searchSongList", parameterObject, PAGE_SIZE);
      	}
      	catch(Exception ex)
      	{
            ex.printStackTrace();
            return null;
      	}
    }
    
    public PaginatedList searchSongListWithDetails(String keywords) 
    {
    	try
      	{
            Object parameterObject = new SongSearch(keywords);
        	return sqlMapClient.queryForPaginatedList("song.searchSongListWithDetails", parameterObject, PAGE_SIZE);
      	}
      	catch(Exception ex)
      	{
            ex.printStackTrace();
            return null;
      	}
    }

    /* Inner Classes */
    public static class SongSearch 
    {
      private List keywordList = new ArrayList();

      public SongSearch(String keywords) 
      {
        StringTokenizer splitter = new StringTokenizer(keywords, " ", false);
        while (splitter.hasMoreTokens())
        {
          keywordList.add("%" + splitter.nextToken() + "%");
        }
      }

      public List getKeywordList()
      {
        return keywordList;
      }
    }
     
}