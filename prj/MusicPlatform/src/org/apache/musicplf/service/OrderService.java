package org.apache.musicplf.service;

import com.ibatis.common.resources.Resources; 
import com.ibatis.sqlmap.client.SqlMapClient; 
import com.ibatis.sqlmap.client.SqlMapClientBuilder; 
import org.apache.musicplf.domain.*;
import org.apache.musicplf.persistence.sqlmapdao.*;

import com.ibatis.common.util.PaginatedList;
import java.util.List;

public class OrderService 
{

  //Constants
  private static final OrderService instance = new OrderService();
  private static OrderDAOImpl orderDAOImpl = new OrderDAOImpl();
  
  //Constructors 
  public OrderService() 
  {
   
  }

  //Public Methods
  public static OrderService getInstance() 
  {
    return instance;
  }

  //ORDER
  public void insertOrder(Order order)
  {
    try 
    {
       orderDAOImpl.insertOrder(order);
    } 
    finally 
    {
 
    }
  }

  public Order getOrder(int orderId) 
  {
    Order order = null;
    try
    {
        for (int i = 0; i < order.getSongItems().size(); i++)
        {
           Song song = (Song) order.getSongItems().get(i);
        }
    }
    finally
    {
   
    }
    return order;
  }
}
