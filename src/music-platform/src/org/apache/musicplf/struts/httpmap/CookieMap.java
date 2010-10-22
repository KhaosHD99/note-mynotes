package org.apache.musicplf.struts.httpmap;

import org.apache.musicplf.struts.httpmap.BaseHttpMap;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import java.util.Enumeration;

public class CookieMap extends BaseHttpMap
{

  private Cookie[] cookies;

  public CookieMap(HttpServletRequest request) 
  {
    cookies = request.getCookies();
  }

  protected Enumeration getNames() 
  {
    return new CookieEnumerator(cookies);
  }

  protected Object getValue(Object key)
  {
    for (int i = 0; i < cookies.length; i++) {
      if (key.equals(cookies[i].getName())) {
        return cookies[i].getValue();
      }
    }
    return null;
  }

  protected void putValue(Object key, Object value)
  {
    throw new UnsupportedOperationException();
  }

  protected void removeValue(Object key) 
  {
    throw new UnsupportedOperationException();
  }

  /**
   * Cookie Enumerator Class
   */
  private class CookieEnumerator implements Enumeration 
  {

    private int i = 0;

    private Cookie[] cookieArray;

    public CookieEnumerator(Cookie[] cookies) {
      this.cookieArray = cookies;
    }

    public synchronized boolean hasMoreElements() {
      return cookieArray.length > i;
    }

    public synchronized Object nextElement() {
      Object element = cookieArray[i];
      i++;
      return element;
    }

  }

}
