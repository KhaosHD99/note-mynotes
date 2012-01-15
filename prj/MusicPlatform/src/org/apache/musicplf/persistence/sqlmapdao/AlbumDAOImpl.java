package org.apache.musicplf.persistence.sqlmapdao;

import com.ibatis.sqlmap.client.SqlMapClient;
import java.sql.SQLException;
import java.util.List;
import org.apache.musicplf.domain.Album;
import org.apache.musicplf.domain.AlbumWithBLOBs;

public class AlbumDAOImpl 
{
    private SqlMapClient sqlMapClient;

    public AlbumDAOImpl(SqlMapClient sqlMapClient) 
    {
        super();
        this.sqlMapClient = sqlMapClient;
    }

    
    public int deleteByPrimaryKey(Integer id) throws SQLException 
    {
        Album key = new Album();
        key.setId(id);
        int rows = sqlMapClient.delete("album.ibatorgenerated_deleteByPrimaryKey", key);
        return rows;
    }

    public void insert(AlbumWithBLOBs record) throws SQLException
    {
        sqlMapClient.insert("album.ibatorgenerated_insert", record);
    }

    public void insertSelective(AlbumWithBLOBs record) throws SQLException 
    {
        sqlMapClient.insert("album.ibatorgenerated_insertSelective", record);
    }

    

    public AlbumWithBLOBs selectByPrimaryKey(Integer id) throws SQLException 
    {
        Album key = new Album();
        key.setId(id);
        AlbumWithBLOBs record = (AlbumWithBLOBs) sqlMapClient.queryForObject("album.ibatorgenerated_selectByPrimaryKey", key);
        return record;
    }

    

   

    public int updateByPrimaryKeySelective(AlbumWithBLOBs record) throws SQLException 
    {
        int rows = sqlMapClient.update("album.ibatorgenerated_updateByPrimaryKeySelective", record);
        return rows;
    }

    public int updateByPrimaryKey(AlbumWithBLOBs record) throws SQLException
    {
        int rows = sqlMapClient.update("album.ibatorgenerated_updateByPrimaryKeyWithBLOBs", record);
        return rows;
    }

    public int updateByPrimaryKey(Album record) throws SQLException 
    {
        int rows = sqlMapClient.update("album.ibatorgenerated_updateByPrimaryKey", record);
        return rows;
    }

}