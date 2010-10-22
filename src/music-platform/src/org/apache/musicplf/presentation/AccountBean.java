package org.apache.musicplf.presentation;

import com.ibatis.common.resources.Resources;
import com.ibatis.common.util.PaginatedList;
import com.ibatis.sqlmap.client.SqlMapClient;
import com.ibatis.sqlmap.client.SqlMapClientBuilder;

import org.apache.musicplf.domain.Account;
import org.apache.musicplf.persistence.sqlmapdao.AccountDAOImpl;
import org.apache.musicplf.persistence.iface.*;
import org.apache.musicplf.service.AccountService;
import org.apache.musicplf.service.CatalogService;
import org.apache.musicplf.struts.ActionContext;
import org.apache.musicplf.struts.BaseBean;

import java.io.Reader;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

public class AccountBean extends BaseBean  
{
  //Constants
  private static final AccountService accountService= AccountService.getInstance();
	
  /* Private Fields */
  private Account account;
  private int id;
  private String username;
  private String password;
  private String repeatedPassword;
  private boolean authenticated = false;
  

  //Constructors
  public AccountBean() 
  {
	 try
	 {
        account = new Account();
	 }
	 catch(Exception ex)
	 {
		 ex.printStackTrace();
	 }
  }

  //JavaBeans Properties
  public String getUsername() 
  {
    return account.getUsername();
  }

  public void setUsername(String username) 
  {
    account.setUsername(username);
  }

  public String getPassword()
  {
    return account.getPassword();
  }

  public void setPassword(String password)
  {
    account.setPassword(password);
  }

  public String getRepeatedPassword() 
  {
    return repeatedPassword;
  }

  public void setRepeatedPassword(String repeatedPassword)
  {
    this.repeatedPassword = repeatedPassword;
  }

  public Account getAccount()
  {
    return account;
  }

  public void setAccount(Account account) 
  {
    this.account = account;
  }
 
  public boolean getAuthenticated()
  {
    return authenticated;
  }

  public void setAuthenticated(boolean authenticated) 
  {
    this.authenticated = authenticated;
  }
  //Public Methods
  public String newAccount() 
  {
    try 
    {
    	System.out.println("insert username:"+account.getUsername());
    	accountService.insertAccount(account);
    //  account = accountService.getAccount(account.getUsername());
    //  myList = catalogService.getProductListByCategory(account.getFavouriteCategoryId());
     // authenticated = true;
    //  repeatedPassword = null;
      return "success";
    } 
    catch (Exception e) 
    {
         e.printStackTrace();
         return null;
    }
  }

  public String editAccountForm()
  {
    try 
    {
      account = accountService.getAccount(account.getUsername());
      return "success";
    } 
    catch (Exception e)
    {
    	e.printStackTrace();
    	return null;
    }
  }

  public String editAccount()
  {
    try 
    {
       accountService.updateAccount(account);
       return "success";
    } 
    catch (Exception e) 
    {
    	e.printStackTrace();
    	return null;
    }
  }

  /*public String switchMyListPage () {
    if ("next".equals(pageDirection)) 
    {
      myList.nextPage();
    } 
    else if ("previous".equals(pageDirection)) 
    {
      myList.previousPage();
    }
    return "success";
  }
*/
  public String signon()
  {
	try
	{
	  account = accountService.getAccount(account.getUsername(), account.getPassword());

      if (account == null) 
      {
        System.out.println("account is null");
      //  ActionContext.getActionContext().setSimpleMessage("Invalid username or password.  Signon failed.");
        clear();
        return "failure";
      } 
      else 
      {
        System.out.println("account is not null");
        account.setPassword(null);
        //  myList = catalogService.getProductListByCategory(account.getFavouriteCategoryId());
        authenticated = true;
        return "success";
      }
	}
	catch(Exception ex)
	{
		ex.printStackTrace();
		return null;
	}
  }

  public String signoff() 
  {
    ActionContext.getActionContext().getRequest().getSession().invalidate();
    clear();
    return "success";
  }

  public String fileUpload() 
  {
    
    return "success";
  }
  
  /*public boolean isAuthenticated() 
  {
    return authenticated && account != null && account.getUsername() != null;
  }*/

  public void reset() 
  {
    if (account != null) 
    {
   //   account.setBannerOption(false);
   //   account.setListOption(false);
    }
  }

  public void clear() 
  {
    account = new Account();
    repeatedPassword = null;
    authenticated = false;
    System.out.println("clear");
  }

  public boolean isAuthenticated()
  {
    return authenticated && account != null && account.getUsername() != null;
  }
  
  
  
  /*public void validate() 
  {
    ActionContext ctx = ActionContext.getActionContext();
    if (validation != null) {
      if (VALIDATE_EDIT_ACCOUNT.equals(validation) || VALIDATE_NEW_ACCOUNT.equals(validation)) {
        if (VALIDATE_NEW_ACCOUNT.equals(validation)) {
        //  account.setStatus("OK");
          validateRequiredField(account.getUsername(), "User ID is required.");
          if (account.getPassword() == null || account.getPassword().length() < 1 || !account.getPassword().equals(repeatedPassword)) {
            ctx.addSimpleError("Passwords did not match or were not provided.  Matching passwords are required.");
          }
        }
        if (account.getPassword() != null && account.getPassword().length() > 0) {
          if (!account.getPassword().equals(repeatedPassword)) {
            ctx.addSimpleError("Passwords did not match.");
          }
        }
      
      }
    }

  }*/
  /*  validateRequiredField(account.getFirstName(), "First name is required.");
  validateRequiredField(account.getLastName(), "Last name is required.");
  validateRequiredField(account.getEmail(), "Email address is required.");
  validateRequiredField(account.getPhone(), "Phone number is required.");
  validateRequiredField(account.getAddress1(), "Address (1) is required.");
  validateRequiredField(account.getCity(), "City is required.");
  validateRequiredField(account.getState(), "State is required.");
  validateRequiredField(account.getZip(), "ZIP is required.");
  validateRequiredField(account.getCountry(), "Country is required.");*/
}
