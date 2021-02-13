import java.util.Scanner;

public class TestPrintf
{
  public static void main(String[] args)
  {
    // =====================
    //  Displaying integers
    // =====================
    
    // ----
    //  %d
    // ----
    
    // Defult formatting
    // Prints 99
    System.out.printf("%d%n", 99);
    
    // Specifying a width
    // Prints |                  99|
    System.out.printf("|%20d|%n", 99);
    
    // Left-justifying within the specified width
    // Prints |99                  |
    System.out.printf("|%-20d%n", 99);
    
    // Padding with zeros
    // Prints |00000000000000000093|
    System.out.printf("|%020d|%n", 99);
    
    // Print positive numbers with a "+"
    // (Negative numbers always have the "-" included)
    // Prints |                 +99|
    System.out.printf("|%+20d|%n", 99);
    
    // A space before positive numbers
    // A "-" is included for negative numbers as per normal
    // Prints | 93|
    System.out.printf("|% d|%n", 99);
    
    // Use locale-specific thousands separator
    // Prints |10,000,000|
    System.out.printf("|%,d|%n", 10000000);
    
    // Enclose negative numbers within paratheses ("()") and skip the "-"
    // Prints |(36)|
    System.out.printf("|%(d|%n", -36);
    
    // ----
    //  %o
    // ----
        
    // Octal output
    // Prints 135
    System.out.printf("|%o|%n", 93);

    // ----
    //  %x
    // ----
    
    // Hex output
    // Prints 5d
    System.out.printf("|%x|%n", 93);
    
    // ==================================
    //  Displaying floating point values
    // ==================================

    // ----
    //  %f
    // ----
    
    // Floating-point number
    // Prints 10.200000
    System.out.printf("%f%n", 10.2);
    
    // Floating-point number
    // Prints 0.000001
    System.out.printf("%f%n", 0.000001234);
    
    // Floating-point number
    // Prints |123456.79|
    System.out.printf("|%.2f|%n", 123456.789);
    
    // Floating-point number
    // Prints |123456.79|
    System.out.printf("|%8.2f|%n", 123456.789);
    
    // Floating-point number
    // Prints | 123456.79|
    System.out.printf("|%10.2f|%n", 123456.789);
    
    // Floating-point number
    // Prints |123456.79 |
    System.out.printf("|%-10.2f|%n", 123456.789);    
    
    // Floating-point number
    // Prints |0123456.79|
    System.out.printf("|%010.2f|%n", 123456.789);

    // ----
    //  %e
    // ----

    // Floating-point in exponential notation
    // Prints 1.020000e+01
    System.out.printf("%e%n", 10.2);
    
    // Floating-point in exponential notation
    // Prints 1.234000e-06
    System.out.printf("%e%n", 0.000001234);
       
    // Floating-point number
    // Prints |1.23e+05|
    System.out.printf("|%.2e|%n", 123456.789);
    
    // Floating-point number
    // Prints |1.23e+05|
    System.out.printf("|%8.2e|%n", 123456.789);
    
    // Floating-point number
    // Prints |  1.23e+05|
    System.out.printf("|%10.2e|%n", 123456.789);
    
    // Floating-point number
    // Prints |1.23e+05  |
    System.out.printf("|%-10.2e|%n", 123456.789);    
    
    // Floating-point number
    // Prints |001.23e+05|
    System.out.printf("|%010.2e|%n", 123456.789);   

    // ----
    //  %g
    // ----
    
    // Floating-point number, possibly in exponential notation depending
    // on the precision and value
    // Prints 10.2000
    System.out.printf("%g%n", 10.2);
    
    // Floating-point number, possibly in exponential notation depending
    // on the precision and value
    // Prints 1.23400e-06
    System.out.printf("%g%n", 0.000001234);    
    
    // Floating-point number
    // Prints |1.2e+05|
    System.out.printf("|%.2g|%n", 123456.789);
    
    // Floating-point number
    // Prints | 1.2e+05|
    System.out.printf("|%8.2g|%n", 123456.789);
    
    // Floating-point number
    // Prints |   1.2e+05|
    System.out.printf("|%10.2g|%n", 123456.789);
    
    // Floating-point number
    // Prints |1.2e+05   |
    System.out.printf("|%-10.2g|%n", 123456.789);    
    
    // Floating-point number
    // Prints |0001.2e+05|
    System.out.printf("|%010.2g|%n", 123456.789);

    // ----
    //  %a
    // ----
    
    // Floating-point in hexadecimal format
    // Prints 0x1.4b3fd5942cd96p-20
    System.out.printf("%a%n", 0.000001234);    
    
    // ====================
    //  Displaying strings
    // ====================
    
    // ----
    //  %s
    // ----
    
    // Prints the whole string
    // Prints |Hello World|
    System.out.printf("|%s|%n", "Hello World");
    
    // Specify field length
    // Prints |                   Hello World|
    System.out.printf("|%30s|%n", "Hello World");
    
    // Left justify text
    // Prints |Hello World                   |
    System.out.printf("|-30s|%n", "Hello World");
        
    // Specify maximum number of characters
    // Prints |Hello|
    System.out.printf("|%.5s|%n", "Hello World");
    
    // Field width and maximum number of characters
    // Prints |                         Hello|
    System.out.printf("|%30.5s|%n", "Hello World");

    // ----
    //  %h
    // ----
      
    // Prints The String object Welcome to COMP3021 is at hash code dde66912
    String str = "Welcome to COMP3021";
    System.out.printf("The String object %s is at hash code %h%n", str, str);

    // ----
    //  %b
    // ----
    
    // Any type
    // Prints true
    System.out.printf("%b%n", true);
    
    // Any type
    // Prints TRUE    
    System.out.printf("%B%n", true);
    
    // ----
    //  %c
    // ----
    
    // Any type
    // Prints a
    System.out.printf("%c%n", 'a');
    
    // Any type
    // Prints A
    System.out.printf("%C%n", 'a');
  }
}