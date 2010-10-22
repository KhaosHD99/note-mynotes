package org.apache.musicplf.persistence.sqlmapdao;

import com.ibatis.sqlmap.client.SqlMapClient;
import java.sql.SQLException;
import java.util.List;
import org.apache.musicplf.domain.Basictablevalue;

public class BasictablevalueDAOImpl 
{
    private SqlMapClient sqlMapClient;

    public BasictablevalueDAOImpl(SqlMapClient sqlMapClient) {
        super();
        this.sqlMapClient = sqlMapClient;
    }

  
    public int deleteByPrimaryKey(Integer id) throws SQLException 
    {
        Basictablevalue key = new Basictablevalue();
        key.setId(id);
        int rows = sqlMapClient.delete("basictablevalue.ibatorgenerated_deleteByPrimaryKey", key);
        return rows;
    }

    public void insert(Basictablevalue record) throws SQLException 
    {
        sqlMapClient.insert("basictablevalue.ibatorgenerated_insert", record);
    }

    public void insertSelective(Basictablevalue record) throws SQLException 
    {
        sqlMapClient.insert("basictablevalue.ibatorgenerated_insertSelective", record);
    }

  

    public Basictablevalue selectByPrimaryKey(Integer id) throws SQLException 
    {
        Basictablevalue key = new Basictablevalue();
        key.setId(id);
        Basictablevalue record = (Basictablevalue) sqlMapClient.queryForObject("basictablevalue.ibatorgenerated_selectByPrimaryKey", key);
        return record;
    }

   

    

    public int updateByPrimaryKeySelective(Basictablevalue record) throws SQLException 
    {
        int rows = sqlMapClient.update("basictablevalue.ibatorgenerated_updateByPrimaryKeySelective", record);
        return rows;
    }

    public int updateByPrimaryKey(Basictablevalue record) throws SQLException 
    {
        int rows = sqlMapClient.update("basictablevalue.ibatorgenerated_updateByPrimaryKey", record);
        return rows;
    }

   
}