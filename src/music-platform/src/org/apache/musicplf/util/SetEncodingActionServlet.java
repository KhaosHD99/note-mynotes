package org.apache.musicplf.util;

import org.apache.struts.action.ActionServlet;
import javax.servlet.http.HttpServletRequest; 
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException; 
import java.io.IOException; 

public class SetEncodingActionServlet extends ActionServlet 
{
	protected void process(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException 
	{ 
		// TODO Auto-generated method stub 
		//String encoding = getInitParameter("encoding"); 
	//	request.setCharacterEncoding(encoding); 
		request.setCharacterEncoding("utf-8");//
		super.process(request, response); 
	}

}
