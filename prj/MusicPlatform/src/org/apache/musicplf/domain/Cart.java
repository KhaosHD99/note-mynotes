package org.apache.musicplf.domain;

import com.ibatis.common.util.PaginatedArrayList;
import com.ibatis.common.util.PaginatedList;

import java.io.Serializable;
import java.math.BigDecimal;
import java.util.*;

public class Cart implements Serializable 
{
  /* Private Fields */
  private final Map itemMap = Collections.synchronizedMap(new HashMap());
  private final PaginatedList itemList = new PaginatedArrayList(4);
  
  /* JavaBeans Properties */
  public Iterator getCartItems() 
  {
    return itemList.iterator();
  }

  public PaginatedList getCartItemList() 
  {
    return itemList;
  }

  public int getNumberOfSongs() 
  {
    return itemList.size();
  }

  /* Public Methods */
  public Iterator getAllCartItems() 
  {
     List allItems = new ArrayList();
     itemList.gotoPage(0);
     allItems.addAll(itemList);
     while (itemList.nextPage()) 
     {
       allItems.addAll(itemList);
     }
     return allItems.iterator();
  }

  public boolean containsItemId(int songId) 
  {
     return itemMap.containsKey(songId);
  }

  public boolean addSong(Song song) 
  {
	  if (itemMap.get(song.getId()) == null)
      {
    	 itemMap.put(song.getId(), song);
         itemList.add(song);
         return true;
      }
      else
      {
    	  return false;
      }
    //  cartItem.incrementQuantity();
  }


  public boolean removeSongById(int songId) 
  {
    Song song = (Song) itemMap.remove(songId);
    if (song == null) 
    {
      return false;
    } 
    else 
    {
      itemList.remove(song);
      return true;
    }
  }

  public int getSubTotal()
  {
    int subTotal = 0;
    Iterator items = getAllCartItems();
    while (items.hasNext())
    {
      Song song = (Song) items.next();
      subTotal = subTotal+song.getPrice();
    }
    return subTotal;
  }

}
