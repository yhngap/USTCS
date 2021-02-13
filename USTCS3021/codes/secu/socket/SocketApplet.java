/**
 * @version 1.00 1999-10-23
 * @author Cay Horstmann
 */

import java.net.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import javax.swing.*;

public class SocketApplet extends JApplet
{  public SocketApplet() 
   {
      JPanel panel = new JPanel();

      panel.add(new JLabel("Server:"));
      serverField = new JTextField(10);
      panel.add(serverField);

      panel.add(new JLabel("Port:"));
      portField = new JTextField(4);
      panel.add(portField);

      JButton openButton = new JButton("Open");
      panel.add(openButton);
      openButton.addActionListener(
         new ActionListener()
         {  public void actionPerformed(ActionEvent event)
	    {  retrieveInfo( serverField.getText().trim(), 
			Integer.parseInt( portField.getText().trim() ) );
            }
         });


      Container contentPane = getContentPane();
      contentPane.add(panel, "North");

      fileText = new JTextArea();
      contentPane.add(new JScrollPane(fileText), "Center");
   }

   public void retrieveInfo(String server, int port)
   {  
      fileText.append("Opening:" + server + "  at port:" + port+ "\n"); 
      try
      {  Socket s = new Socket(server, port);
	 PrintWriter send = new PrintWriter(s.getOutputStream());
	 send.print("GET \r\n");
	 send.flush(); 

         BufferedReader in = new BufferedReader
            (new InputStreamReader(s.getInputStream()));
         boolean more = true;
         while (more)
         {  String line = in.readLine();
            if (line == null) more = false;
            else
                 fileText.append( line+ "\n"); 
         }
	s.close();
      }
      catch (IOException e)
      {  fileText.append("Error" + e);
      }                                    

      catch (SecurityException e)
      {  fileText.append("Error."+e);
      }
   }

   private JTextField serverField;
   private JTextField portField;
   private JTextArea fileText;
}

