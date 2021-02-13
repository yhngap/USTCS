/**
 * @version 1.01 07 Sep 1996 
 * @author Cay Horstmann
 */

import java.io.*;
import corejava.*;

public class WriteBinaryTest
{  public static void main(String[] args)
   {  Employee[] staff = new Employee[3];

      staff[0] = new Employee("Harry Hacker", 35000, 
         new Day(1989,10,1));
      staff[1] = new Employee("Carl Cracker", 75000, 
         new Day(1987,12,15));
      staff[2] = new Employee("Tony Tester", 38000, 
         new Day(1990,3,15));

      int i;      
      try
      {  DataOutputStream out = new DataOutputStream( 
			        new BufferedOutputStream (
            			new FileOutputStream("employee.dat")));
         for (i = 0; i < staff.length; i++)
            staff[i].writeData(out);
         out.close();
      }
      catch(IOException e)
      {  System.out.print("Error: " + e);
         System.exit(1);
      }
      
   }
}

class Employee
{  public Employee(String n, double s, Day d)
   {  name = n;
      salary = s;
      hireDay = d;
   }
   public Employee() {}

   public void print()
   {  System.out.println(name + " " + salary 
         + " " + hireYear());
   }

   public void raiseSalary(double byPercent)
   {  salary *= 1 + byPercent / 100;
   }

   public int hireYear()
   {  return hireDay.getYear();
   }

   public void writeData(DataOutputStream out) throws IOException
   {  
      out.writeChars( name + "\n" );
      out.writeDouble(salary);
      out.writeInt(hireDay.getYear());
      out.writeInt(hireDay.getMonth());
      out.writeInt(hireDay.getDay());
   }


   private String name;
   private double salary;
   private Day hireDay;
}


