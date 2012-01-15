package org.apache.musicplf.persistence.sqlmapdao;

import com.ibatis.common.resources.Resources;
import com.ibatis.sqlmap.client.SqlMapClient;
import com.ibatis.sqlmap.client.SqlMapClientBuilder;
import java.io.Reader;
import java.nio.charset.Charset;
import java.sql.SQLException;
import java.util.List;
import org.apache.musicplf.domain.Artist;
import org.apache.musicplf.domain.ArtistWithBLOBs;

public class ArtistDAOImpl
{
    private SqlMapClient sqlMapClient;

    public ArtistDAOImpl()
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

    

    public int deleteByPrimaryKey(Integer id) throws SQLException 
    {
        Artist key = new Artist();
        key.setId(id);
        int rows = sqlMapClient.delete("artist.ibatorgenerated_deleteByPrimaryKey", key);
        return rows;
    }

    public void insert(ArtistWithBLOBs record) throws SQLException
    {
        sqlMapClient.insert("artist.ibatorgenerated_insert", record);
    }
    
    public void insertArtist(ArtistWithBLOBs record) throws SQLException
    {
        sqlMapClient.insert("artist.insertArtist", record);
    }

    public void insertSelective(ArtistWithBLOBs record) throws SQLException
    {
        sqlMapClient.insert("artist.ibatorgenerated_insertSelective", record);
    }

    

    public ArtistWithBLOBs selectByPrimaryKey(Integer id) throws SQLException 
    {
        Artist key = new Artist();
        key.setId(id);
        ArtistWithBLOBs record = (ArtistWithBLOBs) sqlMapClient.queryForObject("artist.ibatorgenerated_selectByPrimaryKey", key);
        return record;
    }

   

    public int updateByPrimaryKeySelective(ArtistWithBLOBs record) throws SQLException 
    {
        int rows = sqlMapClient.update("artist.ibatorgenerated_updateByPrimaryKeySelective", record);
        return rows;
    }

    public int updateByPrimaryKey(ArtistWithBLOBs record) throws SQLException 
    {
        int rows = sqlMapClient.update("artist.ibatorgenerated_updateByPrimaryKeyWithBLOBs", record);
        return rows;
    }

    public int updateByPrimaryKey(Artist record) throws SQLException 
    {
        int rows = sqlMapClient.update("artist.ibatorgenerated_updateByPrimaryKey", record);
        return rows;
    }

}