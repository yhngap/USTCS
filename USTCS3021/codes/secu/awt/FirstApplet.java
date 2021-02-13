/**
 * @version 1.20 21 Jun 1998
 * @author Cay Horstmann
 */

import javax.swing.*;

public class FirstApplet extends JApplet   // change
{  public void init()
   {
       JFrame frame = new FirstFrame(); //change
       frame.show();
   }
} 

class FirstFrame extends JFrame
{  public FirstFrame()
   {  setTitle("FirstFrame");
      setSize(300, 200);
   }
}


