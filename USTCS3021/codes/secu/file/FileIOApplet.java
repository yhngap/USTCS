/**
 * @version 1.00 1999-10-23
 * @author Cay Horstmann
 */

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import javax.swing.*;

public class FileIOApplet extends JApplet
{
   public void init()
   {
       JFrame frame = new FileFrame(); 
        frame.setSize(600, 400);
       frame.show();
   }      

}

class FileFrame extends JFrame 
{  public FileFrame()
   {  fileNameField = new JTextField(20);
      JPanel panel = new JPanel();

      panel.add(new JLabel("File name:"));
      panel.add(fileNameField);

      JButton openButton = new JButton("Open");
      panel.add(openButton);
      openButton.addActionListener(
         new ActionListener()
         {  public void actionPerformed(ActionEvent event)
	    {  fileName = fileNameField.getText();
               loadFile(fileName);
            }
         });

      JButton saveButton = new JButton("Save");
      panel.add(saveButton);
      saveButton.addActionListener(
         new ActionListener()
         {  public void actionPerformed(ActionEvent event)
	    {  fileName = fileNameField.getText();
               try { 
		PrintWriter out = new PrintWriter(new
            		FileWriter(fileName));  
		out.print( fileText.getText() );
		out.close(); 
	      }
	      catch( IOException e) {}
            }
         });       

      Container contentPane = getContentPane();
      contentPane.add(panel, "North");

      fileText = new JTextArea();
      contentPane.add(new JScrollPane(fileText), "Center");
   }

   public void loadFile(String filename)
   {  try
      {  fileText.setText("");
         BufferedReader in
            = new BufferedReader(new FileReader(filename));
         String s;
         while ((s = in.readLine()) != null)
         fileText.append(s + "\n");
         in.close();
      }
      catch (IOException e)
      {  fileText.append(e + "\n");
      }
      catch (SecurityException e)
      {  fileText.append("I am sorry, but I cannot do that.");
      }
   }

   private JTextField fileNameField;
   private String fileName;
   private JTextArea fileText;
}

