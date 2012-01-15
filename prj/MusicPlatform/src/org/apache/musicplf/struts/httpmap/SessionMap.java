package org.apache.musicplf.struts.httpmap;

import org.apache.musicplf.struts.httpmap.BaseHttpMap;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.util.Enumeration;

public class SessionMap extends BaseHttpMap {

  private HttpSession session;

  public SessionMap(HttpServletRequest request) {
    this.session = request.getSession();
  }

  protected Enumeration getNames() {
    return session.getAttributeNames();
  }

  protected Object getValue(Object key) {
    return session.getAttribute(String.valueOf(key));
  }

  protected void putValue(Object key, Object value) {
    session.setAttribute(String.valueOf(key), value);
  }

  protected void removeValue(Object key) {
    session.removeAttribute(String.valueOf(key));
  }

}
