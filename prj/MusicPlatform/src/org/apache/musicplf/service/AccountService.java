package org.apache.musicplf.service;

import com.ibatis.common.resources.Resources; 
import com.ibatis.sqlmap.client.SqlMapClient; 
import com.ibatis.sqlmap.client.SqlMapClientBuilder; 
import org.apache.musicplf.domain.Account;
import org.apache.musicplf.persistence.sqlmapdao.*;

import java.util.List;

public class AccountService
{
  //Constants 
  private static final AccountService instance = new AccountService();
  private static AccountDAOImpl accountDAOImpl = new AccountDAOImpl();
  
  //Constructors
  public AccountService()
  {
	
  }

  //Public Methods
  public static AccountService getInstance()
  {
    return instance;
  }

  //ACCOUNT
  public Account getAccount(String username)
  {
	return accountDAOImpl.getAccount(username);
  }

  public Account getAccount(String username, String password)
  {
    return accountDAOImpl.getAccount(username, password);
  }

  public void insertAccount(Account account) 
  {
	  accountDAOImpl.insertAccount(account);
  }

  public void updateAccount(Account account) 
  {
	  accountDAOImpl.updateAccount(account);
  }

 

}
