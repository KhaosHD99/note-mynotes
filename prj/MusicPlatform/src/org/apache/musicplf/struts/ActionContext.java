package org.apache.musicplf.struts;

import org.apache.musicplf.struts.httpmap.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ActionContext 
{
	private static final ThreadLocal localContext = new ThreadLocal();

	  private HttpServletRequest request;
	  private HttpServletResponse response;

	  private Map cookieMap;
	  private Map parameterMap;
	  private Map requestMap;
	  private Map sessionMap;
	  private Map applicationMap;

	  private ActionContext() 
	  {
		  
	  }

	  protected static void initialize(HttpServletRequest request, HttpServletResponse response)
	  {
	      ActionContext ctx = getActionContext();
	      ctx.request = request;
	      ctx.response = response;
	      ctx.cookieMap = null;
	      ctx.parameterMap = null;
	      ctx.requestMap = null;
	      ctx.sessionMap = null;
	      ctx.applicationMap = null;
	  }

	  public void setSimpleMessage(String message) 
	  {
	    getRequestMap().put("message", message);
	  }

	  public void addSimpleError(String message) 
	  {
	     List errors = (List) getRequestMap().get("errors");
	     if (errors == null)
	     {
	       errors = new ArrayList();
	       getRequestMap().put("errors", errors);
	     }
	     errors.add(message);
	  }

	  public boolean isSimpleErrorsExist () 
	  {
	    List errors = (List) getRequestMap().get("errors");
	    return errors != null && errors.size() > 0;
	  }

	  public Map getCookieMap() 
	  {
	    if (cookieMap == null) 
	    {
	      cookieMap = new CookieMap(request);
	    }
	    return cookieMap;
	  }

	  public Map getParameterMap() 
	  {
	    if (parameterMap == null)
	    {
	      parameterMap = new ParameterMap(request);
	    }
	    return parameterMap;
	  }

	  public Map getRequestMap() 
	  {
	    if (requestMap == null) 
	    {
	      requestMap = new RequestMap(request);
	    }
	    return requestMap;
	  }

	  public Map getSessionMap() 
	  {
	    if (sessionMap == null)
	    {
	      sessionMap = new SessionMap(request);
	    }
	    return sessionMap;
	  }

	  public Map getApplicationMap() {
	    if (applicationMap == null) 
	    {
	      applicationMap = new ApplicationMap(request);
	    }
	    return applicationMap;
	  }

	  public HttpServletRequest getRequest() 
	  {
	    return request;
	  }

	  public HttpServletResponse getResponse()
	  {
	    return response;
	  }

	  public static ActionContext getActionContext()
	  {
	    ActionContext ctx = (ActionContext) localContext.get();
	    if (ctx == null)
	    {
	      ctx = new ActionContext();
	      localContext.set(ctx);
	    }
	    return ctx;
	  }
}
