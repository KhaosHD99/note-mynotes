package org.apache.musicplf.persistence.sqlmapdao;

import com.ibatis.common.resources.Resources; 
import com.ibatis.sqlmap.client.SqlMapClient; 
import com.ibatis.sqlmap.client.SqlMapClientBuilder; 
import com.ibatis.sqlmap.client.SqlMapClient;
import java.sql.SQLException;
import java.util.List;
import java.io.Reader;
import org.apache.musicplf.domain.Category;
import com.ibatis.common.util.PaginatedList;
import java.nio.charset.Charset;

public class CategoryDAOImpl 
{
    private SqlMapClient sqlMapClient;

    public CategoryDAOImpl() 
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

    public List getCategoryList()
    {
    //  return queryForList("getCategoryList", null);
    	return null;
    }

    public Category getCategoryById(int categoryId)
    {
    	try
    	{
    		if(sqlMapClient==null)
    			 System.out.println("smc is null");
    		else
    			System.out.println("smc is not null");
    	    return (Category)sqlMapClient.queryForList("category.getCategoryById", categoryId).get(0);
        }
    	catch(Exception ex)
    	{
    		ex.printStackTrace();
    		return null;
    	}
    }
   

    public int deleteByPrimaryKey(Integer id) throws SQLException 
    {
        Category key = new Category();
        key.setId(id);
        int rows = sqlMapClient.delete("category.ibatorgenerated_deleteByPrimaryKey", key);
        return rows;
    }

    public void insert(Category record) throws SQLException
    {
        sqlMapClient.insert("category.ibatorgenerated_insert", record);
    }

    public void insertSelective(Category record) throws SQLException 
    {
        sqlMapClient.insert("category.ibatorgenerated_insertSelective", record);
    }

   

   

    public Category selectByPrimaryKey(Integer id) throws SQLException 
    {
        Category key = new Category();
        key.setId(id);
        Category record = (Category) sqlMapClient.queryForObject("category.ibatorgenerated_selectByPrimaryKey", key);
        return record;
    }

    

   

  

    public int updateByPrimaryKeySelective(Category record) throws SQLException
    {
        int rows = sqlMapClient.update("category.ibatorgenerated_updateByPrimaryKeySelective", record);
        return rows;
    }

    public int updateByPrimaryKeyWithBLOBs(Category record) throws SQLException 
    {
        int rows = sqlMapClient.update("category.ibatorgenerated_updateByPrimaryKeyWithBLOBs", record);
        return rows;
    }

    public int updateByPrimaryKeyWithoutBLOBs(Category record) throws SQLException 
    {
        int rows = sqlMapClient.update("category.ibatorgenerated_updateByPrimaryKey", record);
        return rows;
    }

}