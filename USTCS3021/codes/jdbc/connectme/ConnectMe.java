
import java.sql.*;
import java.util.Properties;
import java.io.InputStream;

public class ConnectMe  {
  public static void main (String args[]) {
    try {
      // register driver
      Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
    } catch (Exception e) {
      System.out.println("Failed to load JDBC/ODBC driver.");
      return;
    }
    try {
      // make connection
      Connection con = DriverManager.getConnection("jdbc:odbc:TestDB", "", "");
      System.out.println("Connected.");

      // get meta data
      DatabaseMetaData dmd = con.getMetaData();
      if (dmd == null) {
        System.out.println ("No database meta data available");
      } else {
	  // print information about the data base
        System.out.println ("Database Product Name   : " + dmd.getDatabaseProductName());
        System.out.println ("Database Product Version: " + dmd.getDatabaseProductVersion());
        System.out.println ("Database Driver Name    : " + dmd.getDriverName());
        System.out.println ("Database Driver Version : " + dmd.getDriverVersion());
      }
	// close connection
      con.close();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
