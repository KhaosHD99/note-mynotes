package org.apache.musicplf.presentation;

import org.apache.musicplf.domain.Cart;
import org.apache.musicplf.domain.*;
import org.apache.musicplf.service.CatalogService;
import org.apache.musicplf.struts.ActionContext;
import org.apache.musicplf.struts.BaseBean;
import java.util.Iterator;
import java.util.Map;

public class CartBean extends BaseBean 
{
  /* Constants */
  private static final CatalogService catalogService = CatalogService.getInstance();

  /* Private Fields */
  private Cart cart = new Cart();
  private int workingSongId;
  private String pageDirection;
  private int testId;
  
  /* JavaBeans Properties */
  public Cart getCart()
  {
    return cart;
  }

  public void setCart(Cart cart)
  {
    this.cart = cart;
  }

  public int getWorkingSongId()
  {
     return workingSongId;
  }

  public void setWorkingSongId(int workingSongId) 
  {
     this.workingSongId = workingSongId;
  }

  public String getPageDirection()
  {
    return pageDirection;
  }

  public void setPageDirection(String pageDirection) 
  {
    this.pageDirection = pageDirection;
  }

  /* Public Methods */

  public String addSongToCart() 
  {
    if (cart.containsItemId(workingSongId)) 
    {
    	return "success";
    } 
    else
    {
       System.out.println("workingSongId:"+workingSongId);
       Song song = catalogService.getSongById(workingSongId);
       cart.addSong(song);
       return "success";
    }
  }

  public String removeSongFromCart()
  {
    if (cart.removeSongById(workingSongId) == false) 
    {
      ActionContext.getActionContext().setSimpleMessage("Attempted to remove null CartItem from Cart.");
      return "failure";
    } 
    else
    {
      return "success";
    }
  }

  public String switchCartPage() 
  {
     if ("next".equals(pageDirection))
     {
       cart.getCartItemList().nextPage();
     } 
     else if ("previous".equals(pageDirection)) 
     {
       cart.getCartItemList().previousPage();
     }
     return "success";
  }

  public String viewCart() 
  {
     return "success";
  }

  public void clear()
  {
     cart = new Cart();
     workingSongId = -1;
     pageDirection = null;
  }

}
