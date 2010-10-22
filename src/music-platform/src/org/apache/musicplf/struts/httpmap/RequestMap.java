package org.apache.musicplf.struts.httpmap;

import org.apache.musicplf.struts.httpmap.BaseHttpMap;
import javax.servlet.http.HttpServletRequest;
import java.util.Enumeration;

public class RequestMap extends BaseHttpMap {

  private HttpServletRequest request;

  public RequestMap(HttpServletRequest request) {
    this.request = request;
  }

  protected Enumeration getNames() {
    return request.getAttributeNames();
  }

  protected Object getValue(Object key) {
    return request.getAttribute(String.valueOf(key));
  }

  protected void putValue(Object key, Object value) {
    request.setAttribute(String.valueOf(key), value);
  }

  protected void removeValue(Object key) {
    request.removeAttribute(String.valueOf(key));
  }

}
