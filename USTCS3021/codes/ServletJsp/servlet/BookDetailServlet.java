/*
Copyright (c) 1998 Sun Microsystems, Inc. All Rights Reserved.

This software is the confidential and proprietary information of Sun
Microsystems, Inc. ("Confidential Information").  You shall not
disclose such Confidential Information and shall use it only in
accordance with the terms of the license agreement you entered into
with Sun.

SUN MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE, OR NON-INFRINGEMENT. SUN SHALL NOT BE LIABLE FOR ANY DAMAGES
SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
THIS SOFTWARE OR ITS DERIVATIVES.

CopyrightVersion 1.0
*/

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import database.*;
import cart.*;

/**
 * This is a simple example of an HTTP Servlet.  It responds to the GET
 * and HEAD methods of the HTTP protocol.  This servlet calls other
 * servlets.
 */
public class BookDetailServlet extends HttpServlet {

    public void init() throws ServletException {
        BookDBFrontEnd bookDBFrontEnd =
            (BookDBFrontEnd)getServletContext().getAttribute(
                "examples.bookstore.database.BookDBFrontEnd");

        if (bookDBFrontEnd == null) {
            getServletContext().setAttribute(
                "examples.bookstore.database.BookDBFrontEnd",
                BookDBFrontEnd.instance());
        }
    }

    public void doGet (HttpServletRequest request,
                       HttpServletResponse response)
        throws ServletException, IOException
    {
        // Get the user's session and shopping cart
        HttpSession session = request.getSession(true);
        ShoppingCart cart =
            (ShoppingCart)session.getAttribute(session.getId());

        // If the user has no cart, create a new one
        if (cart == null) {
            cart = new ShoppingCart();
            session.setAttribute(session.getId(), cart);
        }

	// set content-type header before accessing the Writer
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

	// then write the response
        out.println("<html>" +
                    "<head><title>Book Description</title></head>\n" +

                    "<body  bgcolor=\"#FFFFFF\">\n" +
                    "<center>\n" +
                    "<hr> <br> &nbsp;\n" +
                    "<h1>" +
                    "<font size=\"+3\" color=\"red\">Duke's </font>" +
                    "<font size=\"+3\" color=\"purple\">Bookstore</font>" +
                    "</h1>\n" +
                    "</center>\n" +
                    "<br> &nbsp; <hr> <br> &nbsp;\n");

        //Get the identifier of the book to display
        String bookId = request.getParameter("bookId");
        if (bookId != null) {

            // and the information about the book
            BookDBFrontEnd frontEnd =
                (BookDBFrontEnd)getServletContext().getAttribute(
                    "examples.bookstore.database.BookDBFrontEnd");
            BookDetails bd = frontEnd.getBookDetails(bookId);

            //Print out the information obtained
            out.println("<h2>" + bd.getTitle() + "</h2>\n" +

                        "&nbsp; By <em>" + bd.getFirstName() + ", " +
                        bd.getSurname() + "</em> &nbsp; &nbsp; " +
                        "(" + bd.getYear() + ")<br> &nbsp; <br>\n" +

                        "<h4>Here's what the critics say: </h4>\n" +
                        "<blockquote>" + bd.getDescription() +
                        "</blockquote>\n" +

                        "<h4>Our price: $" + bd.getPrice() + "</h4>\n" +

                        "<center>" +
                        "<p><a href=\"" +
                        "/servlet/CatalogServlet?Buy=" + bookId +
                        "\"> Add this item to your shopping cart.</a></p>" +
                        "</center>\n");
        }
        out.println("</body></html>");
        out.close();
    }

    public String getServletInfo() {
        return "The BookDetail servlet returns information about" +
               "any book that is available from the bookstore.";
    }
}
