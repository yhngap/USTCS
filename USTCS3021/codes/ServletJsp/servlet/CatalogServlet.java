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
 * servlets.  This catalog calls other servlets.
 */
public class CatalogServlet extends HttpServlet {

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
        // For 1st visit: create session
        // For later visits: get session and shopping cart
	HttpSession session = request.getSession(true);
	ShoppingCart cart = (ShoppingCart)session.getAttribute(session.getId());

        if (cart == null) {
			// For 1st visit: create shopping cart
            cart = new ShoppingCart();

           	// Keep track of the shopping cart using session
            session.setAttribute(session.getId(), cart);
        }

	// set content-type header before accessing the Writer
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

	// then write the data of the response
        out.println("<html>" +
                    "<head><title> Book Catalog </title></head>\n" +

                    "<body  bgcolor=\"#ffffff\">\n" +
                    "<center>" +
                    "<hr> <br> &nbsp;\n" +
                    "<h1>" +
                    "<font size=\"+3\" color=\"red\">Duke's </font>" +
                    "<font size=\"+3\" color=\"purple\">Bookstore</font>" +
                    "</h1>\n" +
                    "</center>" +
                    "<br> &nbsp; <hr> <br> &nbsp;\n\n");

        //Information on the books is from the database through its front end
        BookDBFrontEnd frontEnd =
            (BookDBFrontEnd)getServletContext().getAttribute(
                "examples.bookstore.database.BookDBFrontEnd");

        // Additions to the shopping cart
        String bookToAdd = request.getParameter("Buy");
        if (bookToAdd != null) {
            BookDetails book = frontEnd.getBookDetails(bookToAdd);

            cart.add(bookToAdd, book);
            out.println("<p><h3>" +
                        "<font color=\"#ff0000\">\n" +
                        "You just added <i>" + book.getTitle() + "</i> "+
                        "to your shopping cart</font></h3>\n\n");
        }

        //Give the option of checking cart or checking out if cart not empty
        if (cart.getNumberOfItems() > 0) {
            out.println("<table><tr>" +
                        "<th align=\"left\"><a href=\"" +
                        "/servlet/ShowCartServlet" +
                        "\"> Check Shopping Cart</a></th>\n" +

                        "<th>&nbsp;</th>\n" +

                        "<th align=\"right\"><a href=\"" +
                        "/servlet/CashierServlet" +
                        "\"> Buy your Books</a></th>" +
                        "</tr></table>\n\n");
        }

        // Always prompt the user to buy more -- get and show the catalog
        out.println("<br> &nbsp;" +
                    "<h3>Please choose from our selections</h3>\n" +
                    "<center> <table>\n");

        BookDetails[] books = frontEnd.getBooksSortedByTitle();
        int numBooks = frontEnd.getNumberOfBooks();
        for(int i=0; i < numBooks; i++) {
            String bookId = books[i].getBookId();

            //Print out info on each book in its own two rows
            out.println("<tr>" +

                        "<td bgcolor=\"#ffffaa\">\n" +
                        "<a href=\"" +
                        "/servlet/BookDetailServlet?bookId=" +
                        bookId +
                        "\"> <strong>" + books[i].getTitle() +
                        "&nbsp; </strong></a></td>\n" +

                        "<td bgcolor=\"#ffffaa\" rowspan=2>" +
                        "$" + books[i].getPrice() +
                        "&nbsp; </td>\n" +

                        "<td bgcolor=\"#ffffaa\" rowspan=2>" +
                        "<a href=\"" +
                        "/servlet/CatalogServlet?Buy=" + bookId
                        + "\"> &nbsp; Add to Cart &nbsp;</a></td></tr>\n" +

                        "<tr>" +
                        "<td bgcolor=\"#ffffff\">" +
                        "&nbsp; &nbsp; by <em> " + books[i].getFirstName() +
                        " " + books[i].getSurname() + "</em></td></tr>\n\n");
        }

        out.println("</table></center></body></html>");
        out.close();
    }

    public String getServletInfo() {
        return "The Catalog servlet adds books to the user's " +
               "shopping cart and prints the catalog.";

    }
}
