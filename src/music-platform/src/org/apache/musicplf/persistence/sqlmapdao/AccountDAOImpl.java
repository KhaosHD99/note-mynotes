package org.apache.musicplf.persistence.sqlmapdao;

import com.ibatis.common.resources.Resources; 
import com.ibatis.sqlmap.client.SqlMapClient; 
import com.ibatis.sqlmap.client.SqlMapClientBuilder; 
import java.sql.SQLException;
import java.util.List;
import java.io.Reader; 
import java.nio.charset.Charset;
import org.apache.musicplf.domain.Account;

public class AccountDAOImpl 
{
    private SqlMapClient sqlMapClient;

    public AccountDAOImpl() 
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
    
    public Account getAccount(String username) 
    {
    	try
    	{
            return (Account) sqlMapClient.queryForObject("Account.getAccountByUsername", username);
    	}
    	catch(Exception ex)
    	{
    		ex.printStackTrace();
    		return null;
    	}
    }

    /*public List getUsernameList() {
      return queryForList("getUsernameList", null);
    }*/

    public Account getAccount(String username, String password)
    {
      Account account = new Account();
      account.setUsername(username);
      account.setPassword(password);
      
      try
      {
         return (Account) sqlMapClient.queryForObject("Account.getAccountByUsernameAndPassword",account);
  	  }
  	  catch(Exception ex)
  	  {
         ex.printStackTrace();
         return null;
  	  }
    }

    public void insertAccount(Account account)
    {
    	try
    	{
          sqlMapClient.insert("Account.insertAccount",account);
    	}
    	catch(Exception ex)
    	{
          ex.printStackTrace();
    	}
    }

    public void updateAccount(Account account) 
    {
    	try
    	{
          sqlMapClient.update("Account.updateAccount",account);
    	}
    	catch(Exception ex)
    	{
          ex.printStackTrace();
    	}
    }
    
}