package org.apache.musicplf.persistence.sqlmapdao;

import com.ibatis.sqlmap.client.SqlMapClient;
import java.sql.SQLException;
import java.util.List;
import org.apache.musicplf.domain.Recordcompany;

public class RecordcompanyDAOImpl  
{
    private SqlMapClient sqlMapClient;

    public RecordcompanyDAOImpl(SqlMapClient sqlMapClient)
    {
        super();
        this.sqlMapClient = sqlMapClient;
    }

    

    public int deleteByPrimaryKey(Integer id) throws SQLException
    {
        Recordcompany key = new Recordcompany();
        key.setId(id);
        int rows = sqlMapClient.delete("recordcompany.ibatorgenerated_deleteByPrimaryKey", key);
        return rows;
    }

    public void insert(Recordcompany record) throws SQLException 
    {
        sqlMapClient.insert("recordcompany.ibatorgenerated_insert", record);
    }

    public void insertSelective(Recordcompany record) throws SQLException 
    {
        sqlMapClient.insert("recordcompany.ibatorgenerated_insertSelective", record);
    }

    public Recordcompany selectByPrimaryKey(Integer id) throws SQLException 
    {
        Recordcompany key = new Recordcompany();
        key.setId(id);
        Recordcompany record = (Recordcompany) sqlMapClient.queryForObject("recordcompany.ibatorgenerated_selectByPrimaryKey", key);
        return record;
    }

   

   
    
    
    public int updateByPrimaryKeySelective(Recordcompany record) throws SQLException 
    {
        int rows = sqlMapClient.update("recordcompany.ibatorgenerated_updateByPrimaryKeySelective", record);
        return rows;
    }

    public int updateByPrimaryKeyWithBLOBs(Recordcompany record) throws SQLException 
    {
        int rows = sqlMapClient.update("recordcompany.ibatorgenerated_updateByPrimaryKeyWithBLOBs", record);
        return rows;
    }

    public int updateByPrimaryKeyWithoutBLOBs(Recordcompany record) throws SQLException 
    {
        int rows = sqlMapClient.update("recordcompany.ibatorgenerated_updateByPrimaryKey", record);
        return rows;
    }

}