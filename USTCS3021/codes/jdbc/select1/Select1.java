import java.sql.*;
import java.util.Properties;
import java.io.InputStream;

public class Select1  {
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

	// create Statement object
	Statement stmt = con.createStatement();

	// form query: selection everything from the Books table
	String query = "SELECT ISBN, Title, Price " +
		         "FROM Books";	

	// execute query
	ResultSet rs =  stmt.executeQuery( query );
      
	// print out record one by one
	while (rs.next())
	{
		for (int i = 1; i <= 3; i++)
      	{
			System.out.print( rs.getString(i) + " | ");
		}
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
