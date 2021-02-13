import java.sql.*;
import java.util.Properties;
import java.io.InputStream;

public class Update  {
  public static void main (String args[]) {
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
      Connection con = DriverManager.getConnection(dataSource, username, password);
      System.out.println("Connected.");

	// create statement
	Statement stmt = con.createStatement();

	// form query: select all Books by McGraw-Hill
	String selectQuery =
  "SELECT Authors.Name, Books.Title, Publishers.Name, Books.Price " +
  "FROM Books, Authors, Publishers, BooksAuthors " +
  "WHERE Publishers.Publisher_Id = Books.Publisher_Id " +
  "AND  Books.ISBN = BooksAuthors.ISBN " +
  "AND  BooksAuthors.Author_Id = Authors.Author_Id " +
  "AND Publishers.Name= 'McGraw-Hill' ";

     // execute query
      ResultSet rs =stmt.executeQuery(selectQuery);

	// print out info
      int num=1;
	while (rs.next())
	{
		System.out.print(" Record #" + num++ + ":  ");
		for (int i=1; i<=4; i++)
			System.out.print( rs.getString(i) );
		System.out.println();
	}

	// slash prices for McGraw-Hill books by 0.5
	String command =
"UPDATE Books " +
"SET Price = Price - "  + "0.5" +
" WHERE Books.Publisher_Id = " +
"(SELECT Publisher_Id FROM Publishers WHERE Name = 'McGraw-Hill')";

      stmt.executeUpdate(command);


	 // retrieve McGraw-Hill books again to see if prices have been reduced
	System.out.println("\n After price slash");
      rs =stmt.executeQuery(selectQuery);
      num=1;
	while (rs.next())
	{
		System.out.print(" Record #" + num++ +":  ");
		for (int i=1; i<=4; i++)
			System.out.print( rs.getString(i) );
		System.out.println();
	}


	// undo price slash
	command =
"UPDATE Books " +
"SET Price = Price + "  + "0.5" +
" WHERE Books.Publisher_Id = " +
"(SELECT Publisher_Id FROM Publishers WHERE Name = 'McGraw-Hill')";

      stmt.executeUpdate(command);

	 // retrieve McGraw-Hill books again to see if prices have been restored
      System.out.println("\n After undoing price slash");
	rs =stmt.executeQuery(selectQuery);
      num=1;
	while (rs.next())
	{
		System.out.print(" Record #" + num++ +":  ");
		for (int i=1; i<=4; i++)
			System.out.print( rs.getString(i) );
		System.out.println();
	}


      // close connection
      con.close();
    }
    catch( Exception e ) {
      e.printStackTrace();
    }
  }
}
