package org.apache.musicplf.struts;

import java.util.List;
import java.util.Map;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import javax.servlet.ServletRequest;
import javax.servlet.http.HttpServletRequest;
import org.apache.struts.action.ActionMapping;



public class BaseBean extends ActionForm 
{
	public void reset(ActionMapping mapping, ServletRequest request) 
	{
	    ActionContext.initialize((HttpServletRequest)request, null);
	    reset();
	}

	  public void reset(ActionMapping mapping, HttpServletRequest request) 
	  {
	     ActionContext.initialize((HttpServletRequest)request, null);
	     reset();
	  }

	  public ActionErrors validate(ActionMapping mapping, ServletRequest request) 
	  {
	    ActionContext.initialize((HttpServletRequest)request, null);
	    ActionContext ctx = ActionContext.getActionContext();
	    Map requestMap = ctx.getRequestMap();

	    List errorList = null;
	    requestMap.put("errors",errorList);
	    validate();
	    errorList = (List) requestMap.get("errors");
	    ActionErrors actionErrors = null;
	    if (errorList != null && !errorList.isEmpty()) {
	      actionErrors = new ActionErrors();
	      actionErrors.add(ActionErrors.GLOBAL_ERROR, new ActionError("global.error"));
	    }
	    return actionErrors;
	  }

	  public ActionErrors validate(ActionMapping mapping, HttpServletRequest request)
	  {
	      ActionContext.initialize(request, null);
	      ActionContext ctx = ActionContext.getActionContext();
	      Map requestMap = ctx.getRequestMap();

	      List errorList = null;
	      requestMap.put("errors",errorList);
	      validate();
	      errorList = (List) requestMap.get("errors");
	      ActionErrors actionErrors = null;
	      if (errorList != null && !errorList.isEmpty())
	      {
	         actionErrors = new ActionErrors();
	         actionErrors.add(ActionErrors.GLOBAL_ERROR, new ActionError("global.error"));
	      }
	      return actionErrors;
	  }

	  public void validate()
	  {
		  
	  }

	  public void reset() 
	  {
		  
	  }

	  public void clear()
	  {
		  
	  }

	  protected void validateRequiredField(String value, String errorMessage) 
	  {
	     if (value == null || value.trim().length() < 1) 
	     {
	        ActionContext.getActionContext().addSimpleError(errorMessage);
	     }
	  }
}
