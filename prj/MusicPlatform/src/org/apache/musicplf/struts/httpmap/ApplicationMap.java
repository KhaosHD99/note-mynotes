package org.apache.musicplf.struts.httpmap;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import java.util.Enumeration;

public class ApplicationMap extends BaseHttpMap
{
  private ServletContext context;

  public ApplicationMap(HttpServletRequest request) 
  {
    context = request.getSession().getServletContext();
  }

  protected Enumeration getNames()
  {
    return context.getAttributeNames();
  }

  protected Object getValue(Object key)
  {
    return context.getAttribute(String.valueOf(key));
  }

  protected void putValue(Object key, Object value)
  {
    context.setAttribute(String.valueOf(key), value);
  }

  protected void removeValue(Object key)
  {
    context.removeAttribute(String.valueOf(key));
  }

}
