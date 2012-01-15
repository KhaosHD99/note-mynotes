package org.apache.musicplf.domain;

import java.io.Serializable;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

public class Order
{
  //Private Fields
  private int id;
  private String username;
  private int totalPrice;
  private Date orderDate;
  private List songItems = new ArrayList();

  /* JavaBeans Properties */
  public int getId() 
  {
    return id;
  }

  public void setId(int orderId)
  {
    this.id = orderId;
  }

  public String getUsername() 
  {
    return username;
  }

  public void setUsername(String username) 
  {
    this.username = username;
  }

  public Date getOrderDate() 
  {
    return orderDate;
  }

  public void setOrderDate(Date orderDate) 
  {
    this.orderDate = orderDate;
  }

  public int getTotalPrice()
  {
    return totalPrice;
  }

  public void setTotalPrice(int totalPrice) 
  {
    this.totalPrice = totalPrice;
  }

  public void setSongItems(List songItems) 
  {
    this.songItems = songItems;
  }

  public List getSongItems() 
  {
    return songItems;
  }

  /* Public Methods */
  public void initOrder(Account account, Cart cart)
  {
     username = account.getUsername();
     orderDate = new Date();
     totalPrice = cart.getSubTotal();
      
     Iterator i = cart.getAllCartItems();
     while (i.hasNext())
     {
        Song song = (Song) i.next();
        songItems.add(song);
     }
  }
}
