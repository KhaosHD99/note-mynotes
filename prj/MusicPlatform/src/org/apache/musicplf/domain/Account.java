package org.apache.musicplf.domain;

import java.io.Serializable;


public class Account implements Serializable 
{
  // Private Fields
  private int id;
  private String username;
  private String password;
  private String email;
  private int state;
  private String regdate;
  private String remark;
  
  /* JavaBeans Properties */
  public int getId() 
  {
     return id;
  }

  public void setId(int id) 
  {
     this.id = id;
  }
  
  public String getUsername() 
  {
     return username;
  }

  public void setUsername(String username) 
  {
     this.username = username;
  }

  public String getPassword() 
  {
     return password;
  }

  public void setPassword(String password) 
  {
     this.password = password;
  }

  public String getEmail() 
  {
     return email;
  }

  public void setEmail(String email) 
  {
     this.email = email;
  }
  
  public String getRegdate() 
  {
	 return regdate;
  }
  
  public void setRegdate(String regdate) 
  {
	 this.regdate = regdate;
  }
	  
  public int getState() 
  {
     return state;
  }

  public void setState(int state)
  {
     this.state = state;
  }
  
  public String getRemark() 
  {
	 return remark;
  }
  
  public void setRemark(String remark)
  {
	 this.remark = remark;
  }
 
}
