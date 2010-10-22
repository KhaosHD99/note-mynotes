package org.apache.musicplf.persistence.sqlmapdao;

import com.ibatis.sqlmap.client.SqlMapClient;
import java.sql.SQLException;
import java.util.List;
import org.apache.musicplf.domain.Basictable;

public class BasictableDAOImpl 
{
    private SqlMapClient sqlMapClient;

    public BasictableDAOImpl(SqlMapClient sqlMapClient)
    {
        super();
        this.sqlMapClient = sqlMapClient;
    }

    

    public int deleteByPrimaryKey(Integer id) throws SQLException
    {
        Basictable key = new Basictable();
        key.setId(id);
        int rows = sqlMapClient.delete("basictable.ibatorgenerated_deleteByPrimaryKey", key);
        return rows;
    }

    public void insert(Basictable record) throws SQLException 
    {
        sqlMapClient.insert("basictable.ibatorgenerated_insert", record);
    }

    public void insertSelective(Basictable record) throws SQLException 
    {
        sqlMapClient.insert("basictable.ibatorgenerated_insertSelective", record);
    }

    public Basictable selectByPrimaryKey(Integer id) throws SQLException 
    {
        Basictable key = new Basictable();
        key.setId(id);
        Basictable record = (Basictable) sqlMapClient.queryForObject("basictable.ibatorgenerated_selectByPrimaryKey", key);
        return record;
    }

    public int updateByPrimaryKeySelective(Basictable record) throws SQLException
    {
        int rows = sqlMapClient.update("basictable.ibatorgenerated_updateByPrimaryKeySelective", record);
        return rows;
    }

    public int updateByPrimaryKeyWithBLOBs(Basictable record) throws SQLException 
    {
        int rows = sqlMapClient.update("basictable.ibatorgenerated_updateByPrimaryKeyWithBLOBs", record);
        return rows;
    }

    public int updateByPrimaryKeyWithoutBLOBs(Basictable record) throws SQLException 
    {
        int rows = sqlMapClient.update("basictable.ibatorgenerated_updateByPrimaryKey", record);
        return rows;
    }

}