 
import java.io.*;
import javax.servlet.*;

public class SimpleGenericServlet extends GenericServlet 
{      public void service (ServletRequest request,
                            ServletResponse response)
             throws ServletException, IOException
       {
           response.setContentType("text/plain");
           PrintWriter out = response.getWriter();
           out.println("Hello World!!");
           out.close();
       } 
}


