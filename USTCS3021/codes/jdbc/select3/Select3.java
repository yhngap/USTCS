import java.sql.*;
import java.util.Properties;
import java.io.InputStream;

public class Select3  {
  public static void main (String args[]) {
    String driverPrefixURL = "jdbc:odbc:";
    String drivers = null;
    String username = null;
    String password = null;
    String dataSource = null;

    try {
      // Look for resource file 'odbc.datasource'
      InputStream is = ClassLoader.getSystemResourceAsStream ("odbc.datasource");
      Properties p = new Properties();
      p.load (is);


      // get driver and and register driver
	drivers = p.getProperty("jdbc.drivers");
	if (drivers !=null)
		System.setProperty("jdbc.drivers", drivers);
       else
		throw new Exception ();

      // get other information
      dataSource = p.getProperty("datasource.name");
      if (dataSource == null)
        throw new Exception ();
      username = p.getProperty("datasource.username", "");
      password = p.getProperty("datasource.password", "");
    } catch (Exception e) {
      System.out.println("Unable to read resource to get data source");
      return;
    }
    try {
	// make connection
      Connection con = DriverManager.getConnection(driverPrefixURL+dataSource, username, password);
      System.out.println("Connected.");

	// create statement
	Statement stmt = con.createStatement();

	// form query: select all Books by McGraw-Hill
	String query = 
  "SELECT Authors.Name, Books.Title, Publishers.Name, Books.Price " +
  "FROM Books, Authors, Publishers, BooksAuthors " +
  "WHERE Publishers.Publisher_Id = Books.Publisher_Id " +
  "AND  Books.ISBN = BooksAuthors.ISBN " +
  "AND  BooksAuthors.Author_Id = Authors.Author_Id " +
  "AND Publishers.Name= 'McGraw-Hill' ";
	
     // execute query
      ResultSet rs = stmt.executeQuery(query);

      int num=1;
	while (rs.next())
	{
		System.out.println(" Record #" + num++);
		System.out.print( rs.getString(1) );
		System.out.print( rs.getString(2) );		
		System.out.print( rs.getString(3) );
		System.out.print( rs.getString(4) );						
		System.out.println("");
	}

      // close connection
      con.close();
    }
    catch( Exception e ) {
      e.printStackTrace();
    }
  }
}
