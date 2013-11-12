package wschat;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;


public class Starter extends JFrame implements ActionListener{

    private static Toolkit kit = Toolkit.getDefaultToolkit();
    Dimension screenSize = kit.getScreenSize();
    private int locX = screenSize.width/3;
    private int locY = screenSize.height/3;
    
    private JTextField user_name = null;
    private JButton butt = null;
    private JPanel pan = null;
    
    private String user = null;
    
    
    public static void main(String[] args)
    {
	new Starter().launch();
    }
    
    public void launch()
    {
	this.setBounds(locX, locY,500,500);
	this.setVisible(true);
	this.setTitle("login");
	pan = new JPanel();
	pan.setLayout(null);
	this.getContentPane().add(pan);
	this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	
	user_name = new JTextField();
	user_name.setBounds(10,10,200,50);
	pan.add(user_name);
	
	butt = new JButton("Login");
	butt.addActionListener(new ActionListener()
	{
	    public void actionPerformed(ActionEvent e)
	    {
		user = user_name.getText().trim();
		new ChatFrame(user).init();
		setVisible(false);
	    }
	});
	butt.setBounds(220,10, 50, 50);
	pan.add(butt);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
	// TODO Auto-generated method stub
	
    }

}
