package org.apache.musicplf.persistence.sqlmapdao;

import java.io.Reader;
import java.nio.charset.Charset;
import com.ibatis.common.resources.Resources; 
import com.ibatis.sqlmap.client.SqlMapClient; 
import com.ibatis.sqlmap.client.SqlMapClientBuilder; 
import org.apache.musicplf.domain.Order;
import com.ibatis.common.util.PaginatedList;

public class OrderDAOImpl 
{
  private SqlMapClient sqlMapClient;
  protected static final int PAGE_SIZE = 4;
  
  public OrderDAOImpl() 
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

  public PaginatedList getOrdersByUsername(String username)
  {
    //return queryForPaginatedList("getOrdersByUsername", username, 10);
	  return null;
  }

  public Order getOrder(int orderId)
  {
    Order order = null;
    Object parameterObject = new Integer(orderId);
  //  order = (Order) queryForObject("getOrder", parameterObject);
  //  order.setLineItems(queryForList("getLineItemsByOrderId", new Integer(order.getOrderId())));
    return order;
  }

  public void insertOrder(Order order) 
  {
	  try
	  {
          sqlMapClient.insert("Order.insertOrder", order);
      }
	  catch(Exception ex)
	  {
		  ex.printStackTrace();
	  }
   }

  

}
