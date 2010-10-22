package org.apache.musicplf.struts.httpmap;

import org.apache.musicplf.struts.httpmap.BaseHttpMap;
import javax.servlet.http.HttpServletRequest;
import java.util.Enumeration;

public class ParameterMap extends BaseHttpMap {

  private HttpServletRequest request;

  public ParameterMap(HttpServletRequest request) {
    this.request = request;
  }

  protected Enumeration getNames() {
    return request.getParameterNames();
  }

  protected Object getValue(Object key) {
    return request.getParameter(String.valueOf(key));
  }

  protected Object[] getValues(Object key) {
    return request.getParameterValues(String.valueOf(key));
  }

  protected void putValue(Object key, Object value) {
    throw new UnsupportedOperationException("Cannot put value to ParameterMap.");
  }

  protected void removeValue(Object key) {
    throw new UnsupportedOperationException("Cannot remove value from ParameterMap.");
  }

}
