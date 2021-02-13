import java.sql.*;
import java.util.Properties;
import java.io.InputStream;

public class ConnectMe1  {
  public static void main (String args[]) {
    String drivers = null;
    String username = null;
    String password = null;
    String dataSource = null;

    try {
      // Look for resource file 'odbc.datasource'
      // Another way to do i/o
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

	// read meta data
      DatabaseMetaData dmd = con.getMetaData();
      if (dmd == null) {
        System.out.println ("No Database Meta Data");
      } else {
        System.out.println ("Database Product Name   : " + dmd.getDatabaseProductName());
        System.out.println ("Database Product Version: " + dmd.getDatabaseProductVersion());
        System.out.println ("Database Driver Name    : " + dmd.getDriverName());
        System.out.println ("Database Driver Version : " + dmd.getDriverVersion());
      }
      // close connection
      con.close();
    }
    catch( Exception e ) {
      e.printStackTrace();
    }
  }
}
