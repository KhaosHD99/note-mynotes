package org.apache.musicplf.struts;

import java.io.File;
import java.io.PrintWriter;
import java.lang.reflect.Method;

import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.FileItemFactory;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.lang.reflect.Method;
import java.util.Iterator;



public class BeanAction extends Action 
{
   public ActionForward execute(ActionMapping mapping,ActionForm form,HttpServletRequest request,HttpServletResponse response)
   throws Exception 
   {
	   String forward = "success";

	    try {
          ActionContext.initialize(request, response);

	      if (form != null)
	      {
            // Explicit Method Mapping
	        Method method = null;
	        String methodName = mapping.getParameter();
	        if (methodName != null && !"*".equals(methodName))
	        {
	          try 
	          {
	            method = form.getClass().getMethod(methodName, null);
	            forward = (String) method.invoke(form, null);
	          } 
	          catch (Exception e) 
	          {
	        	  e.printStackTrace();
	           //   throw new BeanActionException("Error dispatching bean action via method parameter ('" + methodName + "').  Cause: " + e, e);
	          }
	        }

	        // Path Based Method Mapping
	        if (method == null && !"*".equals(methodName)) 
	        {
	          methodName = mapping.getPath();
	          if (methodName.length() > 1) 
	          {
	            int slash = methodName.lastIndexOf("/") + 1;
	            methodName = methodName.substring(slash);
	            if (methodName.length() > 0) 
	            {
	              try 
	              {
	                method = form.getClass().getMethod(methodName, null);
	                forward = (String) method.invoke(form, null);
	              }
	              catch (Exception e) 
	              {
	                e.printStackTrace();
	               // throw new BeanActionException("Error dispatching bean action via URL pattern ('" + methodName + "').  Cause: " + e, e);
	              }
	            }
	          }
	        }
	      }
	      else
	      {
	    	  
	      }

	    }
	    catch (Exception e) 
	    {
	    	e.printStackTrace();
	        request.setAttribute("BeanActionException", e);
	        throw e;
	    }

	    return mapping.findForward(forward);
   }
}
